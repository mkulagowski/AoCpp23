import os
import pathlib
import shutil
import xml.etree.ElementTree as ET

curr = pathlib.Path(__file__).parent.resolve()
srcs_path = os.path.join(curr, 'srcs')
day_files = [path[:-4] for path in os.listdir(srcs_path) if path.endswith('.ixx') and len(path) == 9]
last_num = int(sorted(day_files)[-1][-2:]) + 1

new_name = f'day{last_num:02d}'

with open(os.path.join(curr, 'day_template.ixx'), 'r') as infile:
    filedata = infile.read()
    filedata = filedata.replace('[[NUM]]', f'{last_num:02d}')
    filedata = filedata.replace('[[NUM_ARG]]', f'{last_num}')
    with open(os.path.join(srcs_path, new_name + '.ixx'), 'w') as outfile:
        outfile.write(filedata)

with open(os.path.join(curr, 'day_template.cpp'), 'r') as infile:
    filedata = infile.read()
    filedata = filedata.replace('[[NUM]]', f'{last_num:02d}')
    with open(os.path.join(srcs_path, new_name + '.cpp'), 'w') as outfile:
        outfile.write(filedata)


with open(os.path.join(srcs_path, 'day.ixx'), 'a') as file:
    file.write(f'export import :{new_name};\n')


with open(os.path.join(srcs_path, 'day.cpp'), 'r') as file:
    data = file.read()
nl = '\n'
data = data.replace('default:', f'case {last_num}:{nl: <13}return std::make_shared<Day{last_num:02d}>();{nl: <9}default:')
with open(os.path.join(srcs_path, 'day.cpp'), 'w') as file:
    file.write(data)


open(os.path.join(srcs_path, 'inputs', new_name + '.in'), 'a').close()

ET.register_namespace('', "http://schemas.microsoft.com/developer/msbuild/2003")
et = ET.parse(os.path.join(curr, 'AoCpp23.vcxproj.filters'))
root = et.getroot()

file_group = root[1]
clcomp_node = ET.SubElement(file_group, 'ClCompile')
clcomp_node.set('Include', f'srcs\\{new_name}.ixx')
filt_node = ET.SubElement(clcomp_node, 'Filter')
filt_node.text = 'Header Files'

clcomp_node = ET.SubElement(file_group, 'ClCompile')
clcomp_node.set('Include', f'srcs\\{new_name}.cpp')
filt_node = ET.SubElement(clcomp_node, 'Filter')
filt_node.text = 'Source Files'

input_group = root[2]
none_node = ET.SubElement(input_group, 'None')
none_node.set('Include', f'srcs\\inputs\\{new_name}.in')
filt_node = ET.SubElement(none_node, 'Filter')
filt_node.text = 'Source Files\\inputs'

et.write(os.path.join(curr, 'AoCpp23.vcxproj.filters'))

ET.register_namespace('', "http://schemas.microsoft.com/developer/msbuild/2003")
et = ET.parse(os.path.join(curr, 'AoCpp23.vcxproj'))
root = et.getroot()
itemgroups = [child for child in root if 'ItemGroup' in child.tag and not child.attrib]

file_group, input_group = (itemgroups[0], itemgroups[1]) if 'ClCompile' in itemgroups[0][0].tag else (itemgroups[1], itemgroups[0])

clcomp_node = ET.SubElement(file_group, 'ClCompile')
clcomp_node.set('Include', f'srcs\\{new_name}.ixx')
clcomp_node = ET.SubElement(file_group, 'ClCompile')
clcomp_node.set('Include', f'srcs\\{new_name}.cpp')

none_node = ET.SubElement(input_group, 'None')
none_node.set('Include', f'srcs\\inputs\\{new_name}.in')

et.write(os.path.join(curr, 'AoCpp23.vcxproj'))
