import os

def process_file(name, output, pwd):
    suffix = name[-4:]
    formatname = name[len(pwd):]
    formatname = formatname.replace('_', '-')
    if suffix == '.cpp':
        output.write(f'\\section{{{formatname}}}\n')
        output.write('\\begin{minted}{c++}\n')
        with open(name, 'r') as curr:
            for line in curr:
                output.write(line)
        output.write('\\end{minted}\n')

def begin_document(output):
    output.write('\\documentclass[landscape, 8pt, a4paper, oneside, twocolumn]{extarticle}\n')
    output.write('\\pagenumbering{arabic}\n')
    output.write('\\usepackage{fancyhdr}\n')
    output.write('\\usepackage{minted}\n')
    output.write('\\setminted{breaklines=true, linenos=true, tabsize=2, breaksymbolleft=}\n')
    output.write('\\title{MIPT zzzzz Team Reference}\n')
    output.write('\\begin{document}\n')
    output.write('{\n')
    output.write('\\Large\n')
    output.write('\\maketitle\n')
    output.write('\\tableofcontents\n')
    output.write('}\n')
    output.write('\\thispagestyle{fancy}')
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
