# Make sure you've installed lds gospel library on a *kit-kat* simulator
# Download eveything you want
mkdir -p raw_data
cd raw_data
adb pull `adb shell ls "/data/data/org.lds.ldssa/databases/content-*.db"`
adb pull /data/data/org.lds.ldssa/databases/catalog-1.db
