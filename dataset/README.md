###データセットの作り方をメモしておくよ
* * lec_h2o/dataset/sheet内の"hira.pdf"をたくさん印刷
* hira.pdfにひらがなを書きまくる
* 記入の終わったものをスキャンしまくる
* 一旦GIMP等を用いて2値化を施す
* 処理済みのスキャン画像をlec_h2o/dataset/scanに移動
* lec_h2o/dataset内で
`perl glyphsplit.pl scan/(スキャン画像).png code/_hira3.txt`
→out/pgmにたくさん画像が置かれる(95×95pixel)

