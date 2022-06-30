# FileTimeResetTool

本程序内提供的语言为英语，障碍等级为E(A-F)，即对于非英语为母语者也几乎没有语言障碍。

The language provided within this program is English. To read the instructions in English, please [click here](https://github.com/MucheXD/FileTimeResetTool/README.md#English).

出于某种目的想要修改文件的时间属性？本程序可以帮助你更快速的修改文件时间属性。

---

## 使用方法

### 启动

将需要修改的项拖放至程序图标上来启动程序，支持不同路径下多个文件。

> 如果拖入的项包括文件夹，则程序会自动抽取其内部的文件。文件夹本身不会被包含。

> 如果直接双击启动程序，则程序将无法检测到文件，显示 "No File"

### 选择修改方式

本程序支持4中修改方式

+ "Set Zero" 将会置零时间属性，即将时间重置到 1970年1月1日8:00:00

+ "Random All" 将会为每一个文件的每一项属性分配一个随机的时间，随机的时间可能超过当前时间。

+ "Random A Time" 将会为每一个文件分配一个随机的时间，随机的时间可能超过当前时间。

+ "Input A Time" 允许你自定义时间，选择此项将会展开窗口，你可以在下方定义时间。

### 选择修改模式

+ 本程序支持3种修改模式，依次为创建时间/最后修改时间/访问时间.

+ 使用最上端 "Select All" 选项可全选

### 重置任务

完成设置后，程序顶栏 "Start" 按钮将允许点击，点击该按钮将会开始重置任务。重置任务应该不会花费太多时间。

完成任务后，若显示 "Finish" 则表示全部重置任务均已完成并是成功的，点击程序顶栏 "Finish" 按钮以退出程序。若任务失败，则提示 "Errs occurred" 表明至少有一项的一个属性修改失败。

## 环境说明

以下列出建议的运行环境

> Runtime: Microsoft Visual C++ 2015-2022 Redistributable x64
>
> System: Windows 10 (x64) / Windows 11 (x64)
>
> RAMAvaUse: 32MB

如果您下载的是单文件版本，则需要附加QT6运行时库

## 制作与版权

### 程序制作者

+ 代码逻辑/UI界面: MucheXD 100%

+ 内部图标提供方: iconfont (https://www.iconfont.cn/) / 自行绘制

+ 字体: 默认为微软雅黑，但是非嵌入式的。调用文件: .ui & :/Res/setRandom*.svg

### 版权与许可证

本程序使用以下编译器或支持库

+ VisualStudio 2022

+ QT 6.3.1

本程序使用 LGPL 许可证

详细许可证内容请参阅其对应的官方网站

# English

Want to modify the time attribute of a file for some purpose? This program can help you revise file time attribute conveniently.

---

## Instructions

### start up

Drag and drop the items that you want to be modified onto the program's icon to launch the program, multiple files in different paths is support.

> If the items you dragged includes a folder, the program will automatically extract the files inside it. The folder itself will not be included.

> If you use double-click to start the program, the program will not detect the file and display "No File"

### Select the modification method

This program supports 4 modification methods

+ "Set Zero" will the time property to zero, i.e. reset the time to 1/1/1970 8:00:00

+ "Random All" will assign a random time to each attribute of each file, the random time may exceed the current time.

+ "Random A Time" will assign a random time to each file, the random time may exceed the current time.

+ "Input A Time" allows you to customize the time, selecting this item will expand the window, you can define the time below.

### Select modification mode

+ This program supports 3 modification modes, followed by creation time/last modification time/access time.

+ Use the "Select All" option on the top to select all mode.

### reset task

Once setup is complete, the "Start" button on the top bar of the program will enable, which will start the reset task. The reset task shouldn't take much time.

After completing the task, if "Finish" is displayed, it means that all reset tasks are completed and successful, click the "Finish" button on the top bar of the program to exit the program. If the task fails, the prompt "Errs occurred" indicates that at least one attribute modification failed.

## Environment description

The recommended operating environment is listed below

> Runtime: Microsoft Visual C++ 2015-2022 Redistributable x64
>
> System: Windows 10 (x64) / Windows 11 (x64)
>
> RAMAvaUse: 32MB

If you downloaded the single file version, you will need to attach the QT6 runtime library

## Production and Copyright

### Programmer

+ Code/UI: MucheXD 100%

+ Internal icon provider: iconfont (https://www.iconfont.cn/) / self-drawn

+ Font: Default is Microsoft Yahei, but not embedded. Calling files: .ui & :/Res/setRandom*.svg

### Copyright and License

This program uses the following compilers or support libraries

+ Visual Studio 2022

+ QT 6.3.1

This program is under the LGPL license.

For detailed license content, please refer to its corresponding official website
