#!/usr/bin/perl
#
# 文字割り当て表からコードポイントのリスト（code/_*.txt）を作成し、
# さらにテンプレートから手書きシート（sheet/svg/*.svg, sheet/*.pdf）を作成
#
# usage: perl codesheet.pl [chartable]

use strict;
use warnings;
use File::Basename;

my $chartable = $ARGV[0];  # 文字割り当て表
my $codelist = "code/_" . basename($chartable);  # コードリスト
my $template = "sheet/svg/_template.svg";        # テンプレート
my $svgsheet = "sheet/svg/" . fileparse($chartable, '.txt') . ".svg";
                                                 # 手書きシート（svg）
my $pdfsheet = "sheet/" . fileparse($chartable, '.txt') . ".pdf";
                                                 # 手書きシート（pdf）

# コードリスト作成

open(CHARTABLE, "<:utf8", $chartable) or die "$!";
open(CODELIST, ">:utf8", $codelist) or die "$!";

my @charlist = ();                  # 文字のリスト
while (<CHARTABLE>) {
  $_ =~ s/(\r\n|\n|\r)$//g;         # 行末の改行を削除
  if ($_ !~ /^#/) {                 # コメント行は無視
    my @char = split(/ /);
    # コードポイントを出力
    foreach (@char) {
      print CODELIST sprintf("%04x", unpack("U", "$_"))." # $_\n";
    }
    push(@charlist, @char);         # リスト末尾に追加
  }
}

close(CHARTABLE);
close(CODELIST);

print "wrote codelist: $codelist\n";


# 手書きシート作成

open(TEMPLATE, "<:utf8", $template) or die "$!";
open(SVGSHEET, ">:utf8", $svgsheet) or die "$!";

while (<TEMPLATE>) {
  if (/\*/) {
    my $c = shift(@charlist);
    #$c = '&amp;' if $c eq '&';   　  # 半角 &, <, > は実体参照に置換
    $c = '&lt;' if $c eq '<';
    $c = '&gt;' if $c eq '>';
    $_ =~ s/\*/$c/;
  }
  print SVGSHEET $_;
}

close(TEMPLATE);
close(SVGSHEET);

print "wrote svg-sheet: $svgsheet\n";


# Inkscspe で PDF に変換
system("inkscape -f $svgsheet -A $pdfsheet -T");
print "wrote pdf-sheet: $pdfsheet\n";

exit;
