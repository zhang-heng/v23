#V23
这是一个基于[MITK](http://www.mitk.org/)开发的医学影像二维三维配准项目，提供来自临床手术的前期三维数据及术中二维数据的配准能力和配套的交互操作。
#编译
*step1: 
    获取MITK源码的多种途径: 
        1.https://github.com/MITK/MITK.git
        2.http://www.mitk.org/Download
        3.http://git.mitk.org/MITK.git
×step2:
    编译MITK:([或参看MITK文档](http://docs.mitk.org/2014.03/BuildInstructionsPage.html))
        依赖:...
*step3:
    编译V23:
        在ccmake编译配置项图形界面高级菜单中,"EXTERNAL_MITK_DIR" 设置为/MITK build目录/MITK-build/