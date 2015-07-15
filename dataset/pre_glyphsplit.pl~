#!/usr/bin/perl
#
# 手書きシートのスキャン画像をグリフごとに分割し、out/pgm/uxxxx.pgmとして保存
#
# usage: perl glyphsplit.pl [scanimage] [codelist]
#                             ([optionaloffsetx] [optionaloffsety])

use strict;
use warnings;
use Image::Magick;
use Math::Trig;

my $scanimage = $ARGV[0];     # 手書きシート画像
my $codelist = $ARGV[1];      # 対応するコードリスト
my ($oposx, $oposy) = ($ARGV[2] || 0, $ARGV[3] || 0);  # 任意に加えるオフセット

# 手書きシート画像を開く
my $img = Image::Magick->new;
$img->Read($scanimage);
my ($imgw, $imgh) = $img->Get('width', 'height');  # 手書きシート画像の大きさ
my ($cw, $ch) = ($imgw / 8, $imgh / 11);           # 隅を切り取る大きさ


# 隅を切り取ってそれぞれのマーカーの中心を求める
print "calibrate...\n";
#   左上
my $corner = $img->Clone();
$corner->Crop(width=>$cw, height=>$ch);
my ($ltx, $lty) = &getcenter($corner, $cw, $ch);
$corner->Write('out/temp/templt.bmp'); # 確認用
#   右上
$corner = $img->Clone();
$corner->Crop(width=>$cw, height=>$ch, x=>$imgw-$cw);
my ($rtx, $rty) = &getcenter($corner, $cw, $ch);
$rtx += $imgw - $cw;
$corner->Write('out/temp/temprt.bmp'); # 確認用
#   左下
$corner = $img->Clone();
$corner->Crop(width=>$cw, height=>$ch, y=>$imgh-$ch);
my ($lbx, $lby) = &getcenter($corner, $cw, $ch);
$lby += $imgh - $ch;
$corner->Write('out/temp/templb.bmp'); # 確認用
undef $corner;


# マーカー間の距離を求める
my $bodyw_a = $rtx - $ltx;     # 左上・右上間のx座標の差
my $bodyh_a = $lby - $lty;     # 左上・左下間のy座標の差

# シートの角度を求める
my $theta = atan2($lbx - $ltx, $bodyh_a);


# bodyが内接するように切り抜き
print "crop...\n";
if ($theta >= 0) {
  $img->Crop(width=>$rtx+$lbx-2*$ltx, height=>$lby-$rty, x=>$ltx, y=>$rty);
} else {
  $img->Crop(width=>$rtx-$lbx, height=>$lby+$rty-2*$lty, x=>$lbx, y=>$lty);
}

# 座標を直すために、一旦bmpで保存して開き直す（bmp以外にもjpegやtiffでも可）
$img->Write('out/temp/temp.bmp');
@$img = ();
$img->Read('out/temp/temp.bmp');

# ある程度傾いていれば、シートを回転させて向きを合わせる
if (abs($theta) > 0.0022) {
  print "rotate...\n";
  $img->Rotate(degrees=>$theta*180/pi, color=>'#fff');
} else {
  $theta = 0;
}

# bodyの大きさ・オフセットを求める
my ($bodyw, $bodyh) = ($bodyw_a / cos($theta), $bodyh_a / cos($theta));
my ($bodyosx, $bodyosy) = (($img->Get('width') - $bodyw) / 2 + $oposx,
                           ($img->Get('height') - $bodyh) / 2 + $oposy);

# コードのリストを読み込む
open(CODE, $codelist) or die "$!";
my @code = ();
while (<CODE>) {
  @_ = split(/ /);
  push(@code, $_[0]);
}
close(CODE);

# オリジナルのsvgにおける距離・座標
my ($ltx_o, $lty_o, $markersize_o) = (49.227, 992.911, 20);
my ($rtx_o, $lby_o) = (674.867, 39.451);
my ($a1x_o, $a1y_o, $cellsize_o) = (132.343, 905.311, 28.701);
my ($f1x_o, $a2y_o, $b1x_o) = (313.335, 850.035, 163.524);

# 距離の換算
my ($xr, $yr) = ($bodyw / ($rtx_o - $ltx_o), $bodyh / ($lty_o - $lby_o));
                                           # 換算率
my ($cellw, $cellh) = ($cellsize_o * $xr, $cellsize_o * $yr);
                                           # セルの大きさ
my $a1osx = $bodyosx + ($a1x_o - ($ltx_o + $markersize_o / 2)) * $xr;
                                           # a1セルまでのオフセット(x)
my $a1osy = $bodyosy + (($lty_o + $markersize_o / 2) - ($a1y_o + $cellsize_o)) * $yr;
                                           # a1セルまでのオフセット(y)

my $colos = ($f1x_o - $a1x_o) * $xr;       # 列によるオフセット
my $rowos = ($a1y_o - $a2y_o) * $yr;       # 行によるオフセット
my $cellos = ($b1x_o - $a1x_o) * $xr;      # セルによるオフセット

# セルに切り分けpgmで保存
print "split:\n";
binmode(STDOUT, ":utf8");
foreach my $col (0..2) {
  my $offsetx = $a1osx + $colos * $col;
  print "\n     ".("a  b  c  d  e", "f  g  h  i  j", "k  l  m  n  o")[$col]."\n";
  foreach my $row (0..15) {
    my $offsety = $a1osy + $rowos * $row;
    printf "%2d ", $row + 1;
    foreach my $cell (0..4) {
      my $cellimg = $img->Clone();
      my $cellcode = shift(@code);
      unless ($cellcode eq "3000") { # 全角スペースはスキップ
        $cellimg->Crop(width=>$cellw, height=>$cellh,
                       x=>$offsetx + $cellos * $cell, y=>$offsety);
        $cellimg->Write(type=>"Grayscale", filename=>"out/pgm/u$cellcode.pgm");
      }
      print " " . pack("U", hex($cellcode));
    }
    print "\n";
  }
}

undef $img;

exit;


# ---------------------------------------------

# マーカーの中心を求める
sub getcenter {

  my ($corner, $cw, $ch) = @_;

  # 白黒二値化
  $corner->Quantize(colors=>2, dither=>'True', colorspace=>'Gray');

  # 中心を計算
  my $sumx = my $sumy = 0;
  my $countx = my $county = 0;
  for (my $y = 0; $y < $ch; $y += 2) {
    for (my $x = 0; $x < $cw; $x += 2) {
      if ($corner->Get("pixel[$x, $y]") =~ /^0/) {  # そのピクセルが黒ならば
        $sumx += $x;
        $sumy += $y;
        $countx++;
        $county++;
      }
    }
  }
  return($sumx / $countx, $sumy / $county);
}
