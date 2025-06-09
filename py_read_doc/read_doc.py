import docx
from docx.text.run import Run
import sys
from docx.shared import RGBColor
from lxml import etree


def run_get_att(run:Run,att_name:str)->list:
    return run._element.xpath(att_name)

def run_have_att(run:Run,att_name:str)->bool:
    ret_list = run_get_att(run,att_name)
    return ret_list != []

def run_get_att_value(run:Run,att_name:str,val_name:str)->str:
    att = run_get_att(run,att_name)
    if att:
        namespace = '{http://schemas.openxmlformats.org/wordprocessingml/2006/main}'
        val = att[0].get(f'{namespace}{val_name}')
        return val
    
def run_att_to_str(run:Run)->str:
    return etree.tostring(run._element, encoding='unicode', pretty_print=True)
     
    
def doc_do_text_att(doc_path:str):
    doc = docx.Document(doc_path)
    for paragraph in doc.paragraphs:
        for run in paragraph.runs:
            if run_have_att(run,'.//w:dstrike'):
                print(['double delete'])

            if run_have_att(run,'.//w:strike'):
                print(['delete'])

            if run_get_att_value(run,'.//w:shd','fill') == 'FFFFFF':
                print(['highlight'])

            print(f'{run.text}\n')

            print(run_att_to_str(run))
            print('==============================================')

def doc_recovery(doc_path:str):
    old_text:str = ''
    new_text:str = ''

    doc = docx.Document(doc_path)
    for paragraph in doc.paragraphs:
        for run in paragraph.runs:
            delete_flag = run_have_att(run,'.//w:dstrike') or  run_have_att(run,'.//w:strike')
            highlight_flag = run_get_att_value(run,'.//w:shd','fill') == 'FFFFFF'
            assert not(delete_flag and highlight_flag),"不能同时删除并高亮"

            if delete_flag:
                old_text += run.text
                continue
            
            if highlight_flag:
                new_text += run.text
                continue

            old_text += run.text
            new_text += run.text
        old_text += "\n"
        new_text += "\n"



    return old_text, new_text

if __name__ == "__main__":
    doc_path = 'xxx.docx'  # 替换为实际文档路径
    #doc_path = 'highlight.docx'  # 替换为实际文档路径
    doc_do_text_att(doc_path)

    old_text, new_text = doc_recovery(doc_path)
    print('==================old============================')
    print(old_text)
    # 写入 old.txt 文件
    with open('old.txt', 'w', encoding='utf-8') as file:
        file.write(old_text)
    print('==================new============================')
    print(new_text)
    # 写入 new.txt 文件
    with open('new.txt', 'w', encoding='utf-8') as file:
        file.write(new_text)



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

def doc_read_text_delete(doc_path:str)->str:
    doc = docx.Document(doc_path)
    text = ''

    for para_idx, paragraph in enumerate(doc.paragraphs):
        for run_idx, run in enumerate(paragraph.runs):
            # 尝试获取文字的背景色（shd元素）
            xml_bytes = etree.tostring(run._element, encoding='unicode', pretty_print=True)
            # 打印格式化后的XML
            print(xml_bytes)
    return text

def test_code():
    doc_path = 'highlight.docx'  # 替换为实际文档路径
    text = doc_read_text(doc_path)
    print(text)

    print("===============================")
    text = doc_read_text_highlight(doc_path)
    print(text)
    print("===============================")
    text = doc_read_text_delete(doc_path)
    print(text)