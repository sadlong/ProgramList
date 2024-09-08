##  天气预报系统

**项目准备工作**

首先导入图片，这个方法已经在3种技术模块中提到了，就不再说了。然后就是在.pro文件中第二行加入`Qt += network`和在.h文件中加入一些头文件的声明，头文件申明如下图：



**成果展示**

![1725761197540](C:\Users\123\AppData\Roaming\Typora\typora-user-images\1725761197540.png)



**项目总结**
半成品项目，实话说至少还是学到了一点东西的，下拉框控件：Combo Box，日历控件：Calendar Widget，空白框控件：List Widget，时间显示控件：LCD Number。然后就是项目视频中提到如何添加下拉框的元素和显示系统时间到LCD管上。巩固了添加图片的操作。



**报错解决**

error: No rule to make target '../Qt_Weather_Prs/images/?.jpg', needed by 'debug/qrc_images.cpp'.  Stop.
原因是我的图片是中文名，也不知道为什么改成数字就好使了