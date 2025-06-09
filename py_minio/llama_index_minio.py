import os
from datetime import datetime, timedelta
from llama_index import VectorStoreIndex, ServiceContext
from llama_index.readers.minio import MinioReader
from llama_index.llms import OpenAI

# 配置 MinIO 连接信息
minio_config = {
    "endpoint": "play.min.io",  # MinIO 服务器地址 (示例使用公共测试服务器)
    "access_key": "Q3AM3UQ867SPQQA43P2F",  # 测试用访问密钥
    "secret_key": "zuf+tfteSlswRu7BJ86wekitnifILbZam1KYY3TG",  # 测试用秘密密钥
    "secure": True  # 使用 HTTPS
}

# 配置存储桶和前缀
bucket_name = "llamaindex-demo"  # 示例存储桶
prefix = "documents/"  # 文件夹前缀

def load_and_query_data():
    # 创建 MinioReader 实例
    reader = MinioReader(
        endpoint=minio_config["endpoint"],
        access_key=minio_config["access_key"],
        secret_key=minio_config["secret_key"],
        secure=minio_config["secure"]
    )
    
    # 使用 load_data 加载文件内容，转换为 Document 对象
    documents = reader.load_data(
        bucket_name=bucket_name,
        prefix=prefix,
        file_extractor={
            ".txt": lambda file: file.read().decode("utf-8"),  # 文本文件解析器
            ".pdf": lambda file: extract_text_from_pdf(file),  # 示例 PDF 解析器 (需额外实现)
        }
    )
    
    # 打印加载的文档数量
    print(f"已加载 {len(documents)} 个文档")
    
    # 为每个文档添加额外元数据
    for doc in documents:
        doc.extra_info = {
            "filename": os.path.basename(doc.metadata["filename"]),
            "loaded_at": datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        }
    
    # 创建服务上下文 (可选，用于配置 LLM 和嵌入模型)
    service_context = ServiceContext.from_defaults(
        llm=OpenAI(model="gpt-3.5-turbo", temperature=0.1)
    )
    
    # 构建向量索引
    index = VectorStoreIndex.from_documents(
        documents,
        service_context=service_context
    )
    
    # 创建查询引擎
    query_engine = index.as_query_engine()
    
    # 执行示例查询
    response = query_engine.query("文档中提到了哪些主要技术?")
    
    # 打印查询结果
    print("\n查询结果:")
    print(response)
    
    # 可选: 保存索引以便后续使用
    # index.storage_context.persist(persist_dir="./storage")

# 示例 PDF 解析器函数 (需要安装 pdfplumber 库)
def extract_text_from_pdf(file):
    try:
        import pdfplumber
        with pdfplumber.open(file) as pdf:
            text = ""
            for page in pdf.pages:
                text += page.extract_text()
        return text
    except ImportError:
        print("请安装 pdfplumber 库: pip install pdfplumber")
        return ""

if __name__ == "__main__":
    load_and_query_data()    