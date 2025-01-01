## 工具说明

[DOF 客户端插件](https://github.com/manydots/DofProject)

```sh
# 1.配置管理器-活动解决方案平台(x86)-平台(Win32)
# 2.项目-属性-C/C++(预编译头):不使用预编译头
# 3.dllmain.cpp修改配置-项目生成 DofProject.dll
```

#### 免责声明

- 本项目仅供学习使用，使用本项目时，必须遵守相关法律法规，严禁任何形式的商业用途。

#### 其他说明

- xini_file.h Memory.h @木青大佬自用分享
- 仅供 C++写法参考

#### 自定义功能开启/关闭

```c++
// DLL加载成功后, 默认生成dof.ini文件（部分功能关闭）
// 功能基本仅支持0627
xini_file_t xini_file(config_file); // 初始化配置文件读写类
xini_file["系统配置"]["服务器IP"] = "192.168.200.131";
xini_file["系统配置"]["客户端版本"] = version;
xini_file["系统配置"]["本地日志"] = 0;

xini_file["功能配置"]["本地GM"] = 0;
xini_file["功能配置"]["装备镶嵌"] = 0;
xini_file["功能配置"]["文本粘贴权限"] = 1;
xini_file["功能配置"]["邮件GM标识"] = 1;
xini_file["功能配置"]["关闭回购商店"] = 1;
xini_file["功能配置"]["技能栏显示技能名称"] = 0;
xini_file["功能配置"]["修复233包头"] = 1;
xini_file["功能配置"]["修复移动物品"] = 1;
xini_file["功能配置"]["修复字母显示"] = 1;
xini_file["功能配置"]["禁用最小化其他窗口"] = 0;
xini_file["功能配置"]["缩放优化"] = 0;
xini_file["功能配置"]["修复领主之塔"] = 1;
xini_file["功能配置"]["修复二觉名称乱码"] = 0;
xini_file["功能配置"]["默认创建缔造者"] = 0;

xini_file["颜色配置"]["角色名称颜色"] = "#FFFFFF";
xini_file["颜色配置"]["NPC名称颜色"] = "#E6C89B";

xini_file["键位配置"]["启用"] = 0;
xini_file["键位配置"]["1键CodeKey"] = 55; // 顶部键盘"7"
xini_file["键位配置"]["1槽位X轴"] = 718;
xini_file["键位配置"]["1槽位Y轴"] = 520;
xini_file["键位配置"]["2键CodeKey"] = 56; // 顶部键盘"8"
xini_file["键位配置"]["2槽位X轴"] = 718;
xini_file["键位配置"]["2槽位Y轴"] = 558;
```

#### 其他资源

- [Visual Studio 2022](https://visualstudio.microsoft.com/zh-hans/downloads/)

#### 更新日志

##### 2025-01-01

- 真·14 键位配置(自定义 2 键坐标、KeyCode，开启后必须同步修改 PVF + Frida) 已知问题: 偶发卡顿、修改键位坐标后首次进入游戏偶发崩溃、所有角色共用一套拓展键位
- 真·装备时装镶嵌(Frida 在时装镶嵌部分兼容装备镶嵌) 已知问题: 开孔后孔的颜色不对(未镶嵌徽章时，问题不大)

```js
// 注意: 14键源码中 _627_Hook_4CDCDC push顺序导致坐标是反的
// 默认绑定 55 顶部数字键盘“7”   56 - 顶部数字键盘“8”

// Frida 修改
Memory.protect(ptr(0x08604b1e), 4, "rwx");
ptr(0x08604b1e).writeByteArray([0x83, 0x7d, 0xec, 0x07]);
Memory.protect(ptr(0x08604b8c), 7, "rwx");
ptr(0x08604b8c).writeByteArray([0xc7, 0x45, 0xe4, 0x08, 0x00, 0x00, 0x00]);
Memory.protect(ptr(0x08604a09), 4, "rwx");
ptr(0x08604a09).writeByteArray([0x83, 0x7d, 0x0c, 0x07]);
Memory.protect(ptr(0x086050b1), 7, "rwx");
ptr(0x086050b1).writeByteArray([0xc7, 0x45, 0xec, 0x08, 0x00, 0x00, 0x00]);
Memory.protect(ptr(0x0860511c), 7, "rwx");
ptr(0x0860511c).writeByteArray([0xc7, 0x45, 0xe8, 0x08, 0x00, 0x00, 0x00]);

// PVF 修改
// 常规角色路径：clientonly/hotkeysystem.co
// 缔造角色路径：clientonly/hotkeysystemforcreator.co

[key]
`扩展技能快速键 7`	55
`dungeon`
`right`	55

[key]
`扩展技能快速键 8`	56
`dungeon`
`right`	56
```

##### 2024-12-31

- 本地 GM
- NPC 名称颜色
- 获取客户端版本信息

##### 2024-12-26

- 修复领主之塔异常
- 修复角色二觉职业名称乱码

##### 2024-12-25

- 自定义功能开启/关闭
- 开启本地 DLL 日志

##### 2024-12-23

- 禁用启动游戏时最小化其他窗口 @光头大佬
- 技能栏默认显示技能名称
- 开启台服 DNF 邮件 GM 标识
- 修复 "//移动物品" 命令至脚下

##### 2024-12-19

- 缩放优化(取消[use zoom rate]标签镜头跟随)[关闭]
- 修复字母‘R’&‘I’(0627) @蛐蛐
- 开启[Ctrl+v]粘贴权限 2.0(0627) @蛐蛐
- 修复线条空缺问题(0627) @蛐蛐
- 修复 233 包头客户端异常崩溃(0627/0725)
- 关闭 NPC 重新回购(0627)
