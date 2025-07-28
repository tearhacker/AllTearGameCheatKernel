echo "[+] 正在编译中..."
echo "[+] 正在编译中..."
echo "[+] 正在编译中..."
      /data/data/com.aide.ui/no_backup/ndksupport-1710240003/android-ndk-aide/ndk-build
simulate_progress_bar() {
      local progress=0
      local max_progress=98
      local hang_at=99

      # 打印进度条头部
      echo -ne "[+] 正在编译: ["

      # 模拟20秒的进度条
      for i in $(seq 1 2); do
          # 每秒更新一次进度
          progress=$((i * max_progress / 2))
          # 打印进度条
          echo -ne "#"
          # 打印百分比
          echo -ne " $progress%"

          # 暂停一秒
          sleep 1
      done

      # 在99%处卡住
      echo -ne " 99% #]"
      /data/data/com.aide.ui/no_backup/ndksupport-1710240003/android-ndk-aide/ndk-build > /dev/null 2>&1
      # 检查编译是否成功
if [ $? -ne 0 ]; then
    echo "[+] 编译失败"
    exit 1
fi
      sleep 1

      # 检查libs/arm64-v8a目录下是否有.sh文件
      while true; do
          if ls libs/arm64-v8a/*.sh > /dev/null 2>&1; then
              echo -ne "\r[+] 编译完成: [##################] 100%\n"
              break
          fi
          sleep 1
      done
}

# 调用函数
#simulate_progress_bar


# 如果编译成功，执行其他操作
echo "[+] 编译成功"
# 这里可以添加编译成功后需要执行的命令
echo "[+] 编译结束"


echo "[+] 正在加密"
FILE="独久王者.sh"
output="${TMPDIR}/ImGui"
input="libs/arm64-v8a/独久王者.sh"
space='#\n#独久
'
echo "#!/bin/env sh\n${space}set -eu && output=\"\${TMPDIR}/ImGui\" && cat \$0 | sed \"1,/^# END FILE HEAD/d\" | bzip2 -d -c > \${output} && chmod 777 "\${output}" && "\${output}"    ">  "${FILE}"
echo 'exit 0' >>  "${FILE}"
echo "# END FILE HEAD" >>  "${FILE}"
cat "${input}" | bzip2 -9 -c >>  "${FILE}"
echo "[+] 加密结束"

echo "[+] 正在启动程序"
echo "[+] 正在启动程序"



# 定义目录路径
DIR_PATH="/data/独久"

# 检查目录是否存在
if [ ! -d "$DIR_PATH" ]; then
    # 如果目录不存在，则创建目录
    mkdir -p "$DIR_PATH"
    if [ $? -eq 0 ]; then
        echo "[+] 目录已创建: $DIR_PATH"
    else
        echo "[+] 创建目录失败: $DIR_PATH"
        exit 1
    fi
else
    echo "[+] 目录已存在: $DIR_PATH"
fi

#打开libs/arm64-v8a文件夹二进制文件
#移动到/data/lost+found文件夹命名ImGuiNew
#cp * /data/独久/ROOT-契约共享.sh
#为ImGuiNew文件777权限
#chmod 777 /data/独久/ROOT-契约共享.sh
#运行ImGuiNew
#/data/lost+found/ROOT-契约共享.sh