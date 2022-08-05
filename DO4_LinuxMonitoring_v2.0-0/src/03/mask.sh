function domask {
    all=${#1}  
    ch=""; mask=".*"; char=1
    for ((i=0; i<$all; i++))
    do
        ch="${1:$i:1}"
        mask=$mask$ch
        if [[ $ch = "_" ]]
        then
            char=0
        fi
        if [[ $char -eq 1 ]]
        then
            mask=$mask"+"
        fi
    done
    mask=$mask".*"
    echo $mask
}
