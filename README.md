Life-Fire 2D engine
===================================
Life-Fire is the SG-Studio packages graphics engine base on Qt library, enabling developers do not have to focus on the complex inheritance of Qt, not have to understand all kinds of data type and the use of function, by calling the simple interface function to achieve their 2D effect. Dependent on the power of Qt, this engine has a cross-platform capabilities. Currently supports almost all operating systems, you can do a lot of programmers dream of "write once, deploy everywhere."

Version:
-----------------------------------
Beta v2.56

Progress:
-----------------------------------
Fixed the BUG that continuous switching animation;Add the assertion for start the same type of animation;Abolish the graphics primitives, Now developer can usd Item* to operation Item;Abolish the SC manager;Fixed the problem that the limited length of AES encryption(found the instability of the encryption Chinese);Add some functions to add key and mouse event;Fixed the BUG that player can scroll the view with direction key;Add a function can call signal and slot by QString.Modified SC class makes it’s case unified with the AnimationType;Support all slots to pass parameters(use ParametersStru*);Fixed a lot of warnings;Optimize the engine performance by reducing the number of constructors times;Support developers to create a valid QPixmap* through the engine function;Support to create and modify items by MyPixmap*;Rewrite the asynchronous to synchronous interface, making it easier to use;Changed some widget methods that mustn’t pay attention to private;

Next version:
-----------------------------------
Repair AES encryption Chinese issues, supports direct playback of Gif file.