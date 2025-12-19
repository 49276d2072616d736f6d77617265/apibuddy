# API Buddy

## 项目简介

**API Buddy** 是一个轻量级、高性能的 API 测试工具。
它以 **Markdown (`.md`) 文件作为请求描述载体**，而不是使用 OpenAPI、JSON Schema 或任何重量级规范。

本项目的目标是：

* 极简
* 可控
* 可移植
* 无依赖膨胀（bloat-free）

API Buddy 并不试图“抽象 HTTP”，而是**直接实现 HTTP 协议本身**，以确保行为透明、可预测，并贴近真实网络环境。

---

## 设计理念

* **Bloat-free**：
  不依赖 curl、OpenAPI、libcurl、glibc 的完整实现或任何外部框架。

* **纯 C 实现**：
  所有核心组件均使用 C 编写，包括最小化的 libc 集成，仅实现项目所需功能。

* **Markdown 作为输入**：
  使用 `.md` 文件描述 API endpoint，使 API 文档即测试载荷（Documentation = Payload）。
  ⚡ **新增功能：** 现在可以在 `.md` 文件中定义 HTTP headers（示例见 [`PAYLOAD.md`](./PAYLOAD.md)）。

* **跨平台**：
  目标平台包括 Linux、Windows 和 macOS。

---

## 当前状态

⚠️ **项目仍处于开发阶段**

当前版本支持：

* GET, POST, PUT/UPDATE, DELETE 请求
* 读取 `.md` 文件并解析请求
* CLI 集成，可通过命令行指定 `.md` 文件、目标 IP、主机名和端口执行请求

后续版本将逐步支持：

* 多请求执行
* 响应解析与状态分析

---

## 项目目标（长期）

* 成为 Postman 的极简替代方案
* 保持“零魔法、零隐藏行为”
* 面向系统工程师、底层开发者和安全研究人员

---

# API Buddy

## Overview

**API Buddy** is a lightweight and high-performance API testing tool.
It uses **Markdown (`.md`) files as request payloads**, instead of OpenAPI, JSON schemas, or other heavyweight specifications.

The goal of this project is to be:

* Minimal
* Predictable
* Portable
* Completely bloat-free

Rather than abstracting HTTP away, API Buddy **implements the HTTP protocol directly**, ensuring transparent behavior and precise control over requests.

---

## Design Principles

* **Bloat-free**
  No dependency on curl, OpenAPI, libcurl, or full-featured libc implementations.

* **Pure C implementation**
  Core components are written entirely in C, including a minimal, self-contained libc layer with only the required functionality.

* **Markdown as input**
  `.md` files are used to describe API endpoints, making documentation itself the executable payload.
  ⚡ **New feature:** You can now define HTTP headers directly in the `.md` file (see [`PAYLOAD.md`](./PAYLOAD.md) example).

* **Cross-platform**
  Designed to run on Linux, Windows, and macOS.

---

## Current Status

⚠️ **This project is under active development**

Currently supports:

* GET, POST, PUT/UPDATE, DELETE requests
* Reading and parsing `.md` files
* CLI integration: specify `.md` file, target IP, host, and port to execute requests

Upcoming features:

* Multi-request execution
* Response parsing and analysis

---

## Long-term Goals

* Serve as a minimal alternative to Postman
* Maintain zero hidden behavior and zero magic
* Target system engineers, low-level developers, and security researchers
