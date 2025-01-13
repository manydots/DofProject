#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

// 定义全局常量
const UINT CHARACTER_BASE = 0x1AB7CDC; // 人物基址 + 偏移258（名称）
const UINT SHOP_BASE = 0x1A5FB20; // 商店基址(窗口CALL基址?)
const UINT NOTICE_CALL = 0x9536C0; // 公告CALL(喇叭基址)
const UINT PACKAGE_CALL = 0x744CD0; // 收包头CALL

const UINT SEND_BASE = 0x1AEB6E4; // 发包基址
const UINT CACHE_CALL = 0x1127D60; // 缓冲CALL
const UINT ENCRYPT_CALL1 = 0x1128550; // 加密CALL1 1字节包数据
const UINT ENCRYPT_CALL2 = 0x1128580; // 加密CALL2  CALL1 + 48
const UINT ENCRYPT_CALL4 = 0x11285B0; // 加密CALL4  CALL1 + 96
const UINT ENCRYPT_CALL8 = 0x11285E0; // 加密CALL8  CALL1 + 144
const UINT SEND_CALL = 0x1127EC0; // 发包CALL
const UINT SECRET_CALL = 0x2911D27; // 秘钥CALL

const UINT SHOUT_BASE = 0x1AB950C; // 喊话基址
const UINT SHOUT_CALL = 0x9592A0; // 喊话CALL
#endif // CONSTANTS_H