# fastQDA - a fast and simple alternative for quality-data-analysis 

<p >
  <img align="center" src="https://raw.github.com/gismo141/fastQDA/master/documentation/overview.PNG" alt="fastQDA - Overview"/>
</p>

## What is fastQDA?
The aim of this project is to create an open-source alternative to the market leader MaxQDA. Written in C++ and Qt it is possible to use fastQDA on almost every plattform from mobile to desktop.

<p >
  <img align="center" src="https://raw.github.com/gismo141/fastQDA/master/documentation/main_window.PNG" alt="Mainwindow"/>
</p>

FastQDA is a 3-pane window which enables the user to interact freely with his code- and document-database and his active document in the center of the application. Each code can be colorized and represents the markercolor for the documents.

<p >
  <img align="center" src="https://raw.github.com/gismo141/fastQDA/master/documentation/code_settings.PNG" alt="code-settings-dialog"/>
</p>

Each code consits of a name, a definition, an example (called the anchor), its representing color and its headcode. The code is identified with its unique name. Each settings is adjustable via the 'settings-dialog'.

<p >
  <img align="center" src="https://raw.github.com/gismo141/fastQDA/master/documentation/code_color_settings.PNG" alt="color-dialog"/>
</p>

With the usage of Qt it is possible to create an user-experience that matches the operating-systems style. It is not needed to have a special design for every plattform because everything is already provided by the Qt-framework.

## Usage notes:
At the time of writing the developement is made under Mac OS X with Sublime Text 3 and QtCreator for debugging-purpose. The backend for text-coding is made with the xpdf-toolchain which is freely available.

## Dependencies:

Up to now you need to have at least following programs installed:

- `xpdf`

## How could you contribute?
1. [Fork this project][fork] to your account.
2. [Create a new branch][branch] for the improvements, you intend to make.
3. **Make the changements in your fork.**
4. [Send a pull-request][pr] from your fork’s branch to my `master` branch.
 
You can always use the web-interface to make the changes you want. It helps you automizing the workflow from above.

[fork]: http://help.github.com/forking/
[branch]: https://help.github.com/articles/creating-and-deleting-branches-within-your-repository
[pr]: http://help.github.com/pull-requests/