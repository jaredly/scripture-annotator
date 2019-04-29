# Make sure you've installed lds gospel library on a *kit-kat* simulator
# Download eveything you want
mkdir -p raw_data
cd raw_data
for i in `adb shell ls "/data/data/org.lds.ldssa/databases/content-*.db"`; do
  adb pull `echo $i | tr -d '[:space:]'`
done
adb pull /data/data/org.lds.ldssa/databases/catalog-1.db
