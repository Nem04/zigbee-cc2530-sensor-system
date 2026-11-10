# CC2530 ZigBee 多传感器采集与控制系统

本项目包含基于 TI CC2530 和 Z-Stack 2.3.0 的 ZigBee 协调器、终端节点固件，以及用于串口监控和设备控制的 Windows 上位机。

## 项目内容

| 目录 | 说明 |
| --- | --- |
| `核心源码/coodinate` | 协调器固件，包含完整 Z-Stack 工程。目录名沿用原始项目拼写。 |
| `核心源码/endpoint-1` | 终端节点固件，包含完整 Z-Stack 工程及传感器、执行器驱动。 |
| `核心源码/上位机源码` | 基于 .NET Framework 4.8 的 WinForms 串口上位机。 |
| `串口驱动` | CH341 串口驱动安装程序和原项目安装说明。 |
| `原理图.pdf` | 系统原理图。 |
| `模块电路.pdf` | 模块电路资料。 |

两套固件的核心应用代码均位于：

```text
Projects/zstack/Samples/GenericApp/Source/GenericApp.c
```

终端节点源码还包含 DHT11、DS18B20、RC522、MPU6050、超声波、光敏、人体感应、水位、雨滴、土壤、电流/电压、脉搏等多种传感器驱动，以及 WS2812B、PWM、步进电机和继电器/蜂鸣器控制代码。

## 硬件与软件环境

- MCU：TI CC2530
- ZigBee 协议栈：TI Z-Stack 2.3.0-1.4.0
- 固件 IDE：IAR Embedded Workbench for 8051
- 协调器构建配置：`CoordinatorEB-Pro`
- 终端节点构建配置：`EndDeviceEB-Pro`
- 上位机：Visual Studio 2022、.NET Framework 4.8
- 串口转换芯片：CH341

## 构建固件

1. 安装 IAR Embedded Workbench for 8051。
2. 协调器：打开
   `核心源码/coodinate/ZStack-CC2530-2.3.0-1.4.0/Projects/zstack/Samples/GenericApp/CC2530DB/GenericApp.eww`，
   选择 `CoordinatorEB-Pro` 后编译并下载。
3. 终端节点：打开
   `核心源码/endpoint-1/Projects/zstack/Samples/GenericApp/CC2530DB/GenericApp.eww`，
   选择 `EndDeviceEB-Pro` 后编译并下载。

仓库不包含 IAR 的 `List`、`Obj`、`Exe` 及链接/映射文件等编译产物。TI 提供的 `.lib` 链接库仍然保留，以便工程可重新编译。

## 构建上位机

1. 安装 .NET Framework 4.8 Developer Pack。
2. 使用 Visual Studio 2022 打开
   `核心源码/上位机源码/Program.sln`。
3. 还原/构建 `Program` 项目并运行。

演示登录账号为 `admin`，密码为 `123456`。

上位机通过串口收发以花括号包裹的 JSON 风格键值消息，例如：

```json
{"wendu1":"25"}
{"beep1":"on"}
```

默认串口参数可以在界面上选择。固件中的示例 UART 配置与上位机界面的默认值可能不同，联调时请确认两端波特率、串口号和协议方向一致。

## 使用 CH341 串口

运行 `串口驱动/CH341SerSetup.exe` 安装驱动。安装完成后重新插拔 USB 转串口设备；如系统仍无法识别，请重启电脑后再次检查。

## 说明

本仓库用于保存和展示项目源码及硬件资料，未附独立开源许可证。Z-Stack 源码、TI 链接库及第三方驱动归各自权利人所有；公开发布或再分发前，请确认已获得相应授权。
