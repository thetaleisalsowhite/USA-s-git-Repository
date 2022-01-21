Letter_and_RSJの使い方

まず，Letter_and_RSJ.zipを解凍します．中には，以下のファイルが入っています．

sampleRSJ.tex：RSJ2021に投稿するためのファイル
sampleLetter.tex：レター投稿するためのファイル
sampleBody.tex：論文本体

samplefig2.eps：サンプル図
Readme.txt ：このファイル
rsj2021j.sty：RSJ2021のためのスタイルファイル（sJIS）
jrsj.cls：レター投稿のためのクラスファイル（sJIS）
sampleRSJ.pdf：RSJ2021用論文の出力結果
sampleLetter.pdf：レター用論文の出力結果
JRSJ_Template.doc：レター投稿のためのWordのスタイルファイル

レター同時投稿を行う場合，上から3つのファイルを修正して頂くことになります．
sampleBody.texは，sampleRSJ.texならびに，sampleLetter.texから呼び出されま
すので，このファイルを修正することで，2つのフォーマットに影響します．

なお，レターと講演会論文は，必要な情報が異なるため，タイトルと執筆者情報
を記入するsampleRSJ.texならびに，sampleLetter.texについては，それぞれ修正
をお願いします．具体的には，レターの方に，
・英文タイトル
・執筆者の英文表記
・Abstract
・KeyWords
の追記が必要となりますので，両方のファイルを修正ください．

texliveの2018版の環境では，
$ platex sampleRSJ.tex
$ platex sampleRSJ.tex
$ dvipdfmx sampleRSJ
で講演会版，
$ platex sampleLetter.tex
$ platex sampleLetter.tex
$ dvipdfmx sampleLetter
でレター版の原稿が作成されました．

Wordを使う場合のフォーマットについては，それぞれの論文のフォーマットが置い
てありますので，各自で作成をお願いします．

また，講演会の投稿は，講演会の投稿手順に従って投稿をお願いします．レターの
投稿は，通常の学術論文の投稿手順と同じく，ScolarOneからお願いします．

https://mc.manuscriptcentral.com/jrsj

以上よろしくお願いします．


2020年度版
　2020年5月30日 東京大学 永谷圭司先生

2021年度版に更新　
　2021年5月　RSJ2021出版委員会
