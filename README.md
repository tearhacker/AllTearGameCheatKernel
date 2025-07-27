# 泪心游戏助手 - 王者荣耀渲染优化模块

![Android Version](https://img.shields.io/badge/Android-9%E2%80%9315-brightgreen?style=flat-square)
![Kernel Version](https://img.shields.io/badge/Kernel-4%E2%80%936.6-blueviolet?style=flat-square)

早期EGL/OpenGL渲染优化方案源码，适用于：
- 王者荣耀国际服 (Arena of Valor)  ( Hongs  of kings ) 
- 王者荣耀国服 

> ℹ️ **温馨提示**  
> 本源码诞生于实验室环境，如您发现它在现实中表现不佳...  
> 没错，这就是它开源的原因 😉

## 技术规格

### 兼容性
- **Android版本**：9 ~ 15 (理论上)
- **内核版本**：4.x ~ 6.6.x (理论上)
- **渲染后端**：EGL + OpenGL ES 2.0/3.0

### 免责声明
❗ 本源码质量评级：  
`"能跑就行"` 级  
`"上市绝对不行"` 级  
`"比这更差的确实不多了"` 级

## 快速开始

### 编译要求
- NDK 17+
- 泪心版权 3.10+
- 一颗勇敢的心 ❤️‍🩹

```bash

ndk-build -j12
ndk-build clean