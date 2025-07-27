start=$(date +%s)
/data/local/tmp/ndk/ndk-build -j14
end=$(date +%s)
diff=$(( end - start ))

echo -e "\e[32m:编译耗时：$diff 秒\e[0m"


