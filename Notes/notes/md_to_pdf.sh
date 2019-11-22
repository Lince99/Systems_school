#guida usata: https://jdhao.github.io/2019/05/30/markdown2pdf_pandoc/

pandoc --pdf-engine=context --highlight-style zenburn --toc \
-V colorlinks -V urlcolor=NavyBlue -V toccolor=Red \
-V geometry:"top=2cm, bottom=1.5cm, left=2cm, right=2cm" \
-V subparagraph \
RELAZIONE\ VIRTUALBOX.md  -o relazione_virtualbox.pdf
# -N per aggiungere un indice numerato
