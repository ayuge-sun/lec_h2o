#!/bin/bash

# 実行時に指定された引数の数、つまり変数 $# の値が 3 でなければエラー終了。
if [ $# -ne 3 ]; then
	echo "引数エラー!!" 1>&2
	echo "実行するには"
	echo ""
	echo "    bash kiritori.sh <スキャン画像の名前> <xオフセット値> <yオフセット値>" 
	echo ""
	echo "の順番で、引数を指定してください。" 1>&2
	exit 1
fi

file_name=$(echo $1 | sed -e "s/\.[^.]*$//g")

# 指定された画像を切り取る
# 出力結果は out/pgm に一旦保存される
perl glyphsplit.pl scan/$1 code/_hira3.txt $2 $3

if [ -e ./out/$file_name ]; then
	echo Directory ./out/$file_name exists.
	rm -rf ./out/$file_name
fi

mkdir ./out/$file_name
cp -rf ./out/pgm/* ./out/$file_name/
rename "s/\.pgm/_$file_name\.pgm/;" ./out/$file_name/*.pgm
cp -rf ./out/$file_name/* ./out_train/

echo "神の切り取りが終了したぜぃ!!"
