#!/bin/bash

#guida usata: https://jdhao.github.io/2019/05/30/markdown2pdf_pandoc/
#aggiungere l'opzione -N per avere un indice numerato ad ogni titolo
#pdf engine disponibili: wkhtmltopdf, pdflatex, lualatex, xelatex, pdfroff, context


#dipendenze per debian/ubuntu e derivate:
#sudo apt install pandoc context texlive wkhtmltopdf texlive-xetex #basta context per un pdf base

NOME_RELAZIONE="RELAZIONE_VIRTUALBOX"

#mkdir -p extracted_MEDIA
#touch extracted_ABBR
pandoc --pdf-engine=context \
--highlight-style breezedark \
--toc -V lot \
-V colorlinks -V urlcolor=NavyBlue -V toccolor=Red \
-V geometry:"margin=10mm" -V geometry:"top=2cm, bottom=1.5cm, left=2cm, right=2cm" \
-V margin-left=1cm -V margin-right=1cm -V margin-top=1cm -V margin-bottom=0.5cm \
-V subparagraph -s --listings \
--default-image-extension=.png \
-V papersize=a4 -V documentclass=report \
-f markdown ${NOME_RELAZIONE}.md -o ${NOME_RELAZIONE}.pdf #--verbose
#-V geometry:"top=2cm, bottom=1.5cm, left=2cm, right=2cm" \
#-V extract-media=extracted_MEDIA -V abbreviations=extracted_ABBR \


#pandoc -f markdown ${NOME_RELAZIONE}.md -t pptx -o ${NOME_RELAZIONE}.pptx
