import os

used_dirs = {}

def process_file(name, output, pwd):
    suffix = name[-4:]
    formatname = name[len(pwd):]
    formatname = formatname.replace('_', '-')
    pos = formatname.find('/')
    dirname = formatname[:pos]
    formatname = formatname[pos+1:]
    pos = len(formatname) - 1 - formatname[::-1].find('.')
    formatname = formatname[:pos]
    if not dirname in used_dirs:
        used_dirs[dirname] = 1
        output.write(f'\\section{{{dirname}}}\n')
    if suffix == '.cpp':
        output.write(f'\\subsection{{{formatname}}}\n')
        output.write('\\begin{minted}{c++}\n')
        with open(name, 'r') as curr:
            for line in curr:
                output.write(line)
        output.write('\\end{minted}\n')
    if suffix == '.tex':
        output.write(f'\\subsection{{{formatname}}}\n')
        with open(name, 'r') as curr:
            for line in curr:
                output.write(line)

def begin_document(output):
    output.write('\\documentclass[landscape, 8pt, a4paper, oneside, twocolumn]{extarticle}\n')
    output.write('\\usepackage[compact]{titlesec}\n')
    output.write('\\titlespacing*{\\section}\n')
    output.write('{0pt}{0px plus 1px minus 0px}{-2px plus 0px minus 0px}\n')
    output.write('\\setlength{\\columnseprule}{0.4pt}\n')
    output.write('\\pagenumbering{arabic}\n')
    output.write('\\usepackage[left=0.5cm, right=0.5cm, top=2cm, bottom=0.3cm, a4paper]{geometry}\n')
    output.write('\\usepackage{fancyhdr}\n')
    output.write('\\usepackage{lastpage}\n')
    output.write('\\pagestyle{fancy}\n')
    output.write('\\lhead{Moscow IPT (Kulkov, Mosyagin, Semenov)}\n')
    output.write('\\rhead{Page \\thepage  \\ of \\pageref{LastPage} }\n')
    output.write('\\fancyfoot{}\n')
    output.write('\\headsep 0.2cm\n')
    output.write('\\usepackage{minted}\n')
    output.write('\\setminted{breaklines=true, breakanywhere=true, linenos=false, tabsize=2, breaksymbolleft=}\n')
    output.write('\\title{MIPT zzzzz Team Reference}\n')
    output.write('\\begin{document}\n')
    output.write('{\n')
    output.write('\\Large\n')
    output.write('\\maketitle\n')
    output.write('\\tableofcontents\n')
    output.write('}\n')
    output.write('\\thispagestyle{fancy}\n')
    output.write('\\pagebreak\n')

def end_document(output):
    output.write('\\end{document}\n')


pwd = os.getcwd()

output = open('teambook.tex', 'w')

begin_document(output)

for (dirpath, dirnames, filenames) in os.walk(pwd+'/src'):
    curr = list(map(lambda x : os.path.join(dirpath, x), filenames))
    for x in curr:
        print(f'processing {x}')
        process_file(x, output, pwd+'/src/')

end_document(output)
