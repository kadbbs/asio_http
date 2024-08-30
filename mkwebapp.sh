#!/bin/bash  
  
# 检查是否提供了足够的参数  
if [ "$#" -ne 1 ]; then  
    echo "使用方法: $0  <目标文件夹>"  
    exit 1  
fi  
  
SOURCE_DIR=./tool/webapp
TARGET_DIR=$1
  
# 检查源文件夹是否存在  
if [ ! -d "$SOURCE_DIR" ]; then  
    echo "错误: 源文件夹 '$SOURCE_DIR' 不存在！"  
    exit 1  
fi  
  
# 复制文件夹  
mkdir -p "$TARGET_DIR" && cp -r "$SOURCE_DIR/"* "$TARGET_DIR/"  

# cp -r "$SOURCE_DIR" "$TARGET_DIR/"  
  
# 注意：如果目标文件夹不存在，cp命令会报错，但你可以使用下面的方式避免这个问题  
  
echo "文件夹 '$SOURCE_DIR' 已复制到 '$TARGET_DIR'"