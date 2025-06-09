import docx
import sys
from docx.shared import RGBColor

def doc_read_text(doc_path:str)->str:
    doc = docx.Document(doc_path)
    text = ''
    for paragraph in doc.paragraphs:
        for run in paragraph.runs:
            text += run.text
        text += '\n'
    return text

def doc_read_text_highlight(doc_path:str)->str:
    doc = docx.Document(doc_path)
    text = ''


    for para_idx, paragraph in enumerate(doc.paragraphs):
        for run_idx, run in enumerate(paragraph.runs):
            # 尝试获取文字的背景色（shd元素）
            shd = run._element.xpath('.//w:shd')
            if shd:
                fill = shd[0].get('{http://schemas.openxmlformats.org/wordprocessingml/2006/main}fill')
                if fill:
                    text += f'[HIGHLIGHT:{run.text}]\n'
    return text


if __name__ == "__main__":
    doc_path = 'xxx.docx'  # 替换为实际文档路径
    text = doc_read_text(doc_path)
    print(text)

    print("===============================")
    text = doc_read_text_highlight(doc_path)
    print(text)


