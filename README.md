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
xini_file["系统配置"]["HOOK聊天消息"] = 0;

xini_file["功能配置"]["本地GM"] = 0; // 建议关闭
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

xini_file["颜色配置"]["启用"] = 0;
xini_file["颜色配置"]["角色名称颜色"] = "#FFFFFF";
xini_file["颜色配置"]["NPC名称颜色"] = "#E6C89B"; // Hook

xini_file["键位配置"]["启用"] = 0;
xini_file["键位配置"]["HookKey1"] = 55; // Hook菜单ID
xini_file["键位配置"]["1键X轴"] = 718;
xini_file["键位配置"]["1键Y轴"] = 520;
xini_file["键位配置"]["HookKey2"] = 56; // Hook菜单ID
xini_file["键位配置"]["2键X轴"] = 718;
xini_file["键位配置"]["2键Y轴"] = 558;
```

#### 其他资源

- [Visual Studio 2022](https://visualstudio.microsoft.com/zh-hans/downloads/)

#### 已发现问题

- 本地 GM 开启后游戏启动崩溃几率很大，建议关闭

#### 更新日志

- [历史更新记录](https://github.com/manydots/DofProject/blob/main/CHANGELOG.md)