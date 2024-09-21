foldername="$@"

if [ -d $foldername ]; then 
    echo "Folder Already Exists"
else 
    mkdir $foldername
    cp -r .template/* $foldername
fi