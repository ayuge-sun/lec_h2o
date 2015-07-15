###データセットの作り方をメモしておくよ
####1 紙の準備
* lec_h2o/dataset/sheet内の"hira.pdf"をたくさん印刷
* hira.pdfにひらがなを書きまくる

####2 スキャンと画像の前処理
* 記入の終わったものをスキャンしまくる
* 一旦GIMP等を用いて2値化を施す
* 処理済みのスキャン画像をlec_h2o/dataset/scanに移動

####3 分割のプログラムの実行
* lec_h2o/dataset内で
`mkdir out`
`cd out`
`mkdir pgm`
`mkdir temp`

* lec_h2o/dataset内で
`perl glyphsplit.pl scan/(スキャン画像).png code/_hira3.txt [x ofset] [y_ofset]`
→out/pgmにたくさん画像が置かれる(95×95pixel)

* 出力されるpgmファイルを確認
微妙→[x ofset]と[y ofset]の値を調整し、再度コマンドを叩く
よさ気→次のステップへ

* out/pgmの中身をout_trainの中に移動

