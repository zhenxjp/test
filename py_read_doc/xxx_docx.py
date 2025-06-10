import docx
from docx.text.run import Run
from docx.text.paragraph import Paragraph

from lxml import etree



##########################################################################
# 获取属性
def run_get_att(run:Run,att_name:str)->list:
    return run._element.xpath(att_name)

# 是否存在某属性
def run_have_att(run:Run,att_name:str)->bool:
    ret_list = run_get_att(run,att_name)
    return ret_list != []

# 获取属性值
def run_get_att_value(run:Run,att_name:str,val_name:str)->str:
    att = run_get_att(run,att_name)
    if att is None or len(att) == 0:
        return "xxx_no_att"

    namespace = '{http://schemas.openxmlformats.org/wordprocessingml/2006/main}'
    val = att[0].get(f'{namespace}{val_name}')
    if val is None:
        return "xxx_no_value"
    else:
        return val

    
# 打印element详细信息
def run_att_to_str(run:Run)->str:
    return etree.tostring(run._element, encoding='unicode', pretty_print=True)

##########################################################################
# run是否有删除线
def run_is_delete_in(run:Run,att_name:str)->bool:
    val = run_get_att_value(run,att_name,'val')
    if 'xxx_no_att' == val:
        return False
    else:
        if 'xxx_no_value' == val:
            return True
    
        if '0' ==  val:
            return False
        return True
    
def run_is_delete(run:Run)->bool:
    is_dstrike = run_is_delete_in(run,'.//w:dstrike')
    is_strike = run_is_delete_in(run,'.//w:strike')
    return is_dstrike or is_strike


##########################################################################
# run是否高亮
def run_is_highlight(run:Run)->bool:
    val = run_get_att_value(run,'.//w:shd','val')
    if 'xxx_no_att' == val:
        return False
    else:
        return True
    
##########################################################################


# 获取修改前后的部分
def doc_do_paragraph(paragraphs:list[Paragraph],end:str="\n"):
    old_text:str = ''
    new_text:str = ''
    for paragraph in paragraphs:
        for run in paragraph.runs:
            delete_flag = run_is_delete(run)
            highlight_flag = run_is_highlight(run)
            assert not(delete_flag and highlight_flag),"不能同时删除并高亮"

            element_str = run_att_to_str(run)

            if delete_flag:
                old_text += run.text
                continue
            
            if highlight_flag:
                new_text += run.text
                continue

            old_text += run.text
            new_text += run.text
        old_text += end
        new_text += end

    return old_text, new_text