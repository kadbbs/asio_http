import os  
  
def create_directory_structure(base_dir):  
    # 检查并创建基础目录  
    if not os.path.exists(base_dir):  
        os.makedirs(base_dir)  
        print(f"创建目录：{base_dir}")  
    else:  
        print(f"目录已存在：{base_dir}")  
  
    # 进入基础目录  
    os.chdir(base_dir)  
  
    # 创建子目录  
    subdir = 'templates'  
    if not os.path.exists(subdir):  
        os.makedirs(subdir)  
        print(f"创建子目录：{subdir}")  
  
    # 创建文件  
    files = ['config.json', 'urls.cpp', 'urls.h', 'views.cpp', 'views.h']  
    for file in files:  
        with open(file, 'w') as f:  
            f.write('')  # 写入空内容  
        print(f"创建文件：{file}")  
  
# 调用函数  
base_dir = 'webapp'  
create_directory_structure(base_dir)
