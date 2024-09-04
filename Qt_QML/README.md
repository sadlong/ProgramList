##  QML高级编程

**创建项目**

new project->Qt Quick Application-Empty...省略的步骤和之前的都一样，该选的选，不该选的不选
打开.main.qml文件，配置以下操作，如图所示：
![1725437183863](C:\Users\123\AppData\Roaming\Typora\typora-user-images\1725437183863.png)



右键"/"然后点击add new...，选择Qt->QML File(Qt Quick2)分别创建GreenMenuBar.qml、GreenMenuBarBg.qml和GreenMenuItem.qml。然后在每一个新创建的qml文件中都要和maiin一样Import文件，具体import什么文件差不多和main文件中的一致，效果如图：

![1725438173932](C:\Users\123\AppData\Roaming\Typora\typora-user-images\1725438173932.png)



**报错解决**

在跟着视频敲完一小段之后发现在main.qml文件中一直出现invalid name menuBar的bug，将window改成ApplicationWindow就不会报错了。 

**原因：**`ApplicationWindow` 是一个专门为 Qt Quick Controls 设计的窗口类型，它提供了一个完整的应用窗口，包括菜单栏、工具栏和状态栏等功能，而 `Window` 是更基础的窗口类型，主要用于简单的显示和布局。  代码中，`MenuBar` 和 `Menu` 是 Qt Quick Controls 的组件，它们依赖于 `ApplicationWindow` 来提供完整的功能支持。因此，当你将 `Window` 改为 `ApplicationWindow` 时，它能够正确地渲染和管理菜单栏及其组件。 



**成果展示**

![1725446392020](C:\Users\123\AppData\Roaming\Typora\typora-user-images\1725446392020.png)

免费的课程就是粗糙，做的东西既随意又不完整，仔细一看那个菜单栏还没有对齐，看着真难受，幸好是免费的课，要是不知道花钱买课会是个咋样的结果。跟着敲了几节课的qt项目发现了一个很重要的点，就是你要熟悉这些函数调用，绝大部分的实现其实都是qt自带的函数，这一点的积累肯定是要长期才能形成的。还有就是要搞清楚控件之间的联系啊，层次关系之类的，目前学到这里的感觉就是这样了...代码详细的解释放在了注释里了~