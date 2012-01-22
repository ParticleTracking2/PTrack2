_PTrack2()
{
	local cur prev opts
    COMPREPLY=()
    cur="${COMP_WORDS[COMP_CWORD]}"
    prev="${COMP_WORDS[COMP_CWORD-1]}"
    
    #
    #  The basic options we'll complete.
    #
    opts="chi2 chi2hd chi2hdcuda"
    gopts="-silent -debug -debugwf -chrono -display -nothreads -out -outbin"
    
    case "${prev}" in
		PTrack2)
			COMPREPLY=( $(compgen -W "${opts}" -- ${cur}) )
			return 0
			;;
		chi2)
			local opts1="-i -d -w -cut -maxchi2miniter"
			COMPREPLY=( $(compgen -W "${opts1}${gopts}" -- ${cur}) )
			return 0
			;;
		chi2hd)
			local opts1="-i -d -w -cut -maxchi2miniter -chicut -vorcut -vorsl -2filteri -2filterv"
			COMPREPLY=( $(compgen -W "${opts1}${gopts}" -- ${cur}) )
			return 0
			;;
		chi2hdcuda)
			local opts1="-i -d -w -cut -maxchi2miniter -chicut -vorcut -vorsl -2filteri -2filterv -validateones -device"
			COMPREPLY=( $(compgen -W "${opts1}${gopts}" -- ${cur}) )
			return 0
			;;
		"-i")
			COMPREPLY=( $(compgen -f ${cur}) )		
			return 0
			;;
		*)
		;;
    esac
    
    COMPREPLY=( $(compgen -W "${opts}" -- ${cur}) )
}
complete -F _PTrack2 -o filenames PTrack2
