_main_completer() {
    local cur prev opts interfaces
    COMPREPLY=()
    cur="${COMP_WORDS[COMP_CWORD]}"
    prev="${COMP_WORDS[COMP_CWORD-1]}"
    opts="-s"

    if [[ ${prev} == "-s" ]]; then
        interfaces=$(ls /sys/class/net)
        COMPREPLY=( $(compgen -W "${interfaces}" -- ${cur}) )
        return 0
    fi
}
complete -F _main_completer ./main

