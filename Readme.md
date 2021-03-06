# 构造Delaunay三角形的通用算法----凸包插值算法

> ​	**姓名：朱泳亮			  OUC**

## 一、引言（或问题的提出、研究背景介绍、概述等）

​		三角剖分构造Delaunay三角形也是计算机辅助几何设计研究的重要内容之一。它也广泛地应用在有限元分析和信息可视化等领域。对于仅包含离散点的数据集，可以采用离散点无约束Delaunay三角剖分算法得到强健的三角网络

<img src="https://github.com/Coeur-Bleu/cg2021ZYLDelaunayTriangulation/blob/ba2cfa4ef389a55197c7667123f60add812c421f/pictures/001.jpg" style="zoom:50%;" />

​		所谓三角形剖分，就是对多边形进行三角形划线剖分，在三角剖分问题中，我们常使用Delaunay三角网法则实现Voronoi图，这是一种使用不规则的小面块来逼近和模拟自然界不规则地理单元的一种方法，多用于图像绘制等，是解决相关几何问题强有力的工具。实际上Delaunay就是由多个点构成的一个三角网，其中多个点按照一定的约束规则，两两相连所构成，其约束条件如下：

> 1. 在构成三角形时，总是优先与最近的点相连构成三角形；
> 2. 在多点两两相连的三角网中，不会有一个三角形的外接圆中存在另一个点；
> 3. 对于一个凸四边形的两种剖分，所剖分出的两个三角形中的最小内角最大



## 二、具体的算法（或技术介绍等）

​		在本文所描述的构造Delaunay三角形的算法步骤中，我们将构造过程分为以下四个步骤阶段进行阐述。

> - **Graham扫描法凸包构建**
> - **环切边界法凸包三角剖分**
> - **离散点内插构造三角形**
> - **Lawson算法局部三角形优化LOP(Local Optimization Procedure)**

------

### Graham扫描法凸包构建阶段

​		首先简单阐述凸包（Convex Hull）的概念，平面上的凸包定义为：平面的一个子集S被称为是“凸”的，当且仅当对于任意两点p，s∈S，线段ps都完全属于S。简单来说，就是顾名思义在点集中找到能包含住所有点的，部分点的连线所构成的凸状的多边形。

<img src="https://github.com/Coeur-Bleu/cg2021ZYLDelaunayTriangulation/blob/ba2cfa4ef389a55197c7667123f60add812c421f/pictures/003.jpg" style="zoom: 50%;" />

​		作为该流程中最初的流程阶段，我们当前所拥有的唯一的数据是所有散点的相关信息(位置坐标)，我们首先需要找出最外围的点集构成凸包，我们使用的是Graham扫描法也称极角排序法【时间复杂度：O(nlogn) 】，这是一种较为暴力的方法，基本步骤如下所示：

<img src="https://github.com/Coeur-Bleu/cg2021ZYLDelaunayTriangulation/blob/ba2cfa4ef389a55197c7667123f60add812c421f/pictures/004.jpg" style="zoom: 33%;" />

> **step 1：**从所有绘制在坐标系中的点中找到纵坐标最低的点，记作P0，该点是最先能确定，一定是凸包的构成点，将P0点压入凸包点List内。
>
> **step 2：**计算其余各个点相对于 P0 的幅角 α ，按从小到大的顺序对各个点排序【可以通过计算叉积的方式来进行极角排序】，当两个点与基点P0的幅角α 相同，我们默认将距离P0越小的点越往前排序。由排序可知第二个点P1点也一定是凸包的构成点，将P1点压入凸包点List内。
>
> **step 3：**之后从步骤2求得的那个结果里，把 P1 后面的那个点拿出来做当前点，即 P2 。接下来开始找第三个点：
>
> **step 4：**连接P0和栈顶的那个点，得到直线 L 。看当前点是在直线 L 的右边还是左边。如果在直线的右边就执行step 5；如果在直线上，或者在直线的左边就执行step 6。
>
> **step 5：**如果在右边，则栈顶的那个元素不是凸包上的点，把栈顶元素出栈。执行step 4。
>
> **step 6：**当前点是凸包上的点，把它压入栈，执行step 7。
>
> **step 7：**检查当前的点 P2 是不是步骤3那个结果的最后一个元素。是最后一个元素的话就结束。如果不是的话就把 P2 后面那个点做当前点，返回step 4

### 环切边界法凸包三角剖分阶段

 		简单来说，该阶段就是在凸包点链表中，每次寻找一个由相邻两条凸包边组成的三角形，在该三角形的内部和边界上都不包含凸包上的任何其他点，然后去掉该点得到新的凸包链表，重复这个过程，最终对凸包链表中的点进行三角剖分成功，同时获取所有凸包点构成的三角形链表。

<img src="https://github.com/Coeur-Bleu/cg2021ZYLDelaunayTriangulation/blob/ba2cfa4ef389a55197c7667123f60add812c421f/pictures/005.jpg" style="zoom: 33%;" />

​		在该部分中，我们主要的目的是将所构造的凸包拆分成三角形构成，现在我们就具有了一个包含了所有未连接的离散点的，内部全由三角形构成的多边形，从而为之后的离散点内插入三角形做准备。

​		该阶段代码运行产生图为：【注：该图与上方绘制示意图方向颠倒，原因是由于在MFC程序中画布的坐标系是从上到下，从左到右为正方向】

<img src="https://github.com/Coeur-Bleu/cg2021ZYLDelaunayTriangulation/blob/ba2cfa4ef389a55197c7667123f60add812c421f/pictures/009.png" style="zoom: 80%;" />

### 离散点内插构造三角形阶段

 		一般来说，在对凸包进行三角剖分之后，针对不在凸包上的其余离散点的操作，可采用逐点内插的方法进行剖分。在此算法中，基本步骤如下所示：

> **step 1：**选择尚未构成三角形的离散点，将未被插入的散点依次进行插入
>
> **step 2：**在原图中所割分的三角形中找出其外接圆包含插入点的三角形（称为该点的影响三角形），此时该离散点存在外接圆内的情况又分为三角内与三角外两种情况，针对内外两种情况，在三角形内部时，三角形的对应边为三条边，要构建出三个新三角形存入三角形链表；后者在三角形外部时，三角形对应的为两条边，要新构建出两个三角形存入三角形链表。
>
> **step 3：**删除影响三角形的对应边。
>
> **step 4：**将加入的新点同影响三角形的全部顶 点连接起来，从而完成一个点在Delaunay三角网中的插入过程

该算法阶段步骤的简洁表示如下图所示：

![](https://github.com/Coeur-Bleu/cg2021ZYLDelaunayTriangulation/blob/ba2cfa4ef389a55197c7667123f60add812c421f/pictures/002.png)

### Lawson算法局部三角形优化LOP阶段

​		虽然在上一步中，我们使用离散点内插的方法将所有的离散点都加入了三角形构成中，但也是仅仅保证了所有插入的点构成了三角网，无法保证他们所构成的三角形满足最优，效果往往很差，上一阶段构造后未经过局部优化的三角网代码运行产生图如下图所示：

<img src="https://github.com/Coeur-Bleu/cg2021ZYLDelaunayTriangulation/blob/ba2cfa4ef389a55197c7667123f60add812c421f/pictures/006.png" style="zoom: 67%;" />

​		对此我们进行局部优化LOP的步骤为：

<img src="https://github.com/Coeur-Bleu/cg2021ZYLDelaunayTriangulation/blob/ba2cfa4ef389a55197c7667123f60add812c421f/pictures/007.jpg" style="zoom:50%;" />

> **step 1：**对新形成的三角形进行优化，循环依次寻找到有相邻边的两个三角形
>
> **step 2：**以外接圆准则作检查，判断每组有相邻边的两个三角形相邻边对应顶点是否处于对方三角形的外接圆内。
>
> **step 3：**若在，将四边形内原对角线改为另外一对角线，否则则保持原对角线划分，即完成局部优化过程的处理。

最后可获得优化结果，代码运行产生图为：

<img src="https://github.com/Coeur-Bleu/cg2021ZYLDelaunayTriangulation/blob/ba2cfa4ef389a55197c7667123f60add812c421f/pictures/008.png" style="zoom: 67%;" />



### 三、算法的应用和具体实施方式等

​		Delaunay 三角网的优点是结构良好，数据结构简单，数据冗余度小，存储效率高，与不规则的地面特征和谐一致，可以表示线性特征和迭加任意形状的区域边界，易于更新，可适应各种分布密度的数据等。伴随着计算机技术的发展日益走向成熟。这类将数据换为图形或图像在屏幕上显示出来的技术方法，广泛运用于计算机辅助设计、计算机视觉、人机交互技术、计算机图形学、图像处理等多个领域。

​		**由于具体代码写了800多行过于冗长，故不在此报告中详细解读具体实施方式，详细注释已在附带提交的实验项目中的cg2021ZYLDelaunayTriangulationView.cpp文件中进行了详细的注释。**



### 四、总结与展望，发表个人见解体会、评价等

​		其实在除去不断改进优化的逐点插入法外还存在分治算法和三角网生成算法，这三种算法各有优劣。

​		其中**三角网生成算法**的基本思路是从所有散点中任意找一点，然后找出距离这个点最近的点，两点相连作为一条基线，之后在其右侧运用Delaunay法则去找出相距最短的第三个点进行组合连接构成三角形，再以该三角形的两条新边（从基线起始点到第三点以及第三点到基线终止点）作为新的基线。之后再重复以上步骤进行三角形绘图。

​		而**分治算法**就是将所有散点集合进行一定的拆分，将所拆分出的子集进行三角剖分绘图，再将各个子集所生成的三角网格进行合并，通过不断递归来实现所有点集的三角网绘图。

<img src="https://github.com/Coeur-Bleu/cg2021ZYLDelaunayTriangulation/blob/ba2cfa4ef389a55197c7667123f60add812c421f/pictures/010.png" style="zoom:90%;" />

​		如上图所示，三角网生成法的时间效率最低，分治算法的时间效率最高，逐点插入法效率居中。由于区域生长法本质的缺陷，导致其效率受限，这种方法在80年代中期以后已经很少使用。分治算法时间效率相对较高，但是由于其递归执行，所以需要较大的内存空间，导致其空间效率较低。此外，分治法的数据处理及结果的优化需要的工作量也比较大。逐点插入算法实现简单，时间效率比较高，而运行占用的空间也较小，从时间效率和空间效率综合考虑，性价比最高，因而应用广泛。

### 五、可以适当增加图表、代码等辅助展示手段

> - ​	按照以上步骤，使用C++语言通过在VS上创建的MFC项目，实现了用户可交互的，使用凸包插值算法构造Delaunay三角形的程序。

基本界面如下图所示：

![](https://github.com/Coeur-Bleu/cg2021ZYLDelaunayTriangulation/blob/ba2cfa4ef389a55197c7667123f60add812c421f/pictures/011.png)
