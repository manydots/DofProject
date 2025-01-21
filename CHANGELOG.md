## [更新记录](https://github.com/manydots/DofProject/releases)

##### 2025-01-21

- 默认 HOOK 缓冲 CALL、加密 CALL1、加密 CALL2、加密 CALL4
- 开启 VEH HOOK(//HOOK)
- 关闭 VEH HOOK(//UNHOOK)选择角色前必须手动关闭 VEH HOOK
- 热键默认绑定 F4
- 开启 F4 热键(//HOTKEY)
- 关闭 F4 热键(//UNHOTKEY)
- Hotkey.cpp 补全实现[原贴地址](https://www.52pojie.cn/thread-538578-1-1.html)
- F4 绑定释放技能(//SKILL)
- 释放技能（技能代码,伤害）(//SKILL 22228? 1?) 可缺省、指定技能代码、伤害；默认为男机械觉醒
- 获取角色信息(//GET STATE)

##### 2025-01-13

- 客户端控制台输出调试日志

##### 2025-01-11

- Hook 客户端消息输入(//指令)
- 获取角色名称(//GET NAME)
- 喊话内容(//SHOUT 喊话内容)
- 颜色配置增加启用配置
- 本地 GM 开启后游戏启动崩溃几率很大，建议关闭
- 调整代码结构

##### 2025-01-06

- 修正键位配置描述(删除 dof.ini 重新生成)

##### 2025-01-01

- 真·14 键位配置(自定义 2 键坐标、KeyCode，开启后必须同步修改 PVF + Frida) 已知问题: 偶发卡顿、修改键位坐标后首次进入游戏偶发崩溃、所有角色共用一套拓展键位
- 真·装备时装镶嵌(Frida 在时装镶嵌部分兼容装备镶嵌) 已知问题: 开孔后孔的颜色不对(未镶嵌徽章时，问题不大)

```js
// 注意: 14键源码中 _627_Hook_4CDCDC push顺序导致坐标是反的
// 默认HookKey 55/56  17:L_Ctrl 18:L_Alt

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

// 备注:
`扩展技能快速键 7`	55 ---[55] HookKey1
`扩展技能快速键 8`	56 ---[56] HookKey2
`dungeon`
`right`	17 ---[17] &L_Ctrl
`right`	18 ---[18] &L_Alt


[key]
`扩展技能快速键 7`	55
`dungeon`
`right`	17

[key]
`扩展技能快速键 8`	56
`dungeon`
`right`	18
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
