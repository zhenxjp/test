from minio import Minio
from minio.error import S3Error
import os

def download_pdf_files(bucket_name: str, prefix: str = "", download_dir: str = None):
    """
    从 MinIO 存储桶下载 PDF 文件到本地
    
    参数:
        bucket_name: 存储桶名称
        prefix: 对象名称前缀，用于过滤文件
        download_dir: 本地下载目录，默认为存储桶名称
    """
    # 创建 MinIO 客户端
    client = Minio(
        endpoint="play.min.io",  # 替换为你的 MinIO 服务器地址
        access_key="Q3AM3UQ867SPQQA43P2F",  # 替换为你的访问密钥
        secret_key="zuf+tfteSlswRu7BJ86wekitnifILbZam1KYY3TG",  # 替换为你的秘密密钥
        secure=True  # 是否使用 HTTPS
    )

    # 检查存储桶是否存在
    if not client.bucket_exists(bucket_name):
        print(f"存储桶 {bucket_name} 不存在")
        return

    # 设置下载目录
    if download_dir is None:
        download_dir = bucket_name
    
    # 创建本地下载目录
    os.makedirs(download_dir, exist_ok=True)
    
    # 遍历存储桶中的 PDF 对象
    objects = client.list_objects(bucket_name, prefix=prefix, recursive=True)
    
    print(f"存储桶 {bucket_name} 中发现的 PDF 文件：")
    pdf_count = 0
    downloaded_count = 0
    
    for obj in objects:
        if obj.object_name.lower().endswith('.pdf'):
            pdf_count += 1
            print(f"\n文件 #{pdf_count}: {obj.object_name}")
            
            # 构建本地文件路径
            local_path = os.path.join(download_dir, obj.object_name)
            local_dir = os.path.dirname(local_path)
            
            # 创建必要的子目录
            os.makedirs(local_dir, exist_ok=True)
            
            try:
                # 下载文件
                client.fget_object(bucket_name, obj.object_name, local_path)
                print(f"✅ 已下载到: {local_path}")
                downloaded_count += 1
            except S3Error as e:
                print(f"❌ 下载失败: {e}")
            except Exception as e:
                print(f"❌ 发生未知错误: {e}")
    
    print(f"\n共发现 {pdf_count} 个 PDF 文件，成功下载 {downloaded_count} 个")

if __name__ == "__main__":
    # 示例：下载 my-bucket 存储桶中所有 PDF 文件到本地
    download_pdf_files("my-bucket")
    
    # 示例：下载 my-bucket 存储桶中 documents/ 目录下的 PDF 文件
    # download_pdf_files("my-bucket", "documents/")
    
    # 示例：下载到指定目录
    # download_pdf_files("my-bucket", download_dir="pdf_downloads")    