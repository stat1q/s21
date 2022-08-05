function numgen {
    echo $(($RANDOM % $1))
}

function numgen1 {
    echo $(($RANDOM % $1 + 1))
}

function ipgen {
    echo "83.246."$(numgen 256)"."$(numgen1 254)
}

function numgen2 {
    rez=$(($RANDOM % $1))
    if [[ rez -lt 10 ]]
    then 
        first="0"
    else
        first=""
    fi
    echo $first$rez
}

function timegen {
    echo $(numgen2 24)":"$(numgen2 60)":"$(numgen2 60)
}
