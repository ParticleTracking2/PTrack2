
PTRACK2_G_OPTS="-silent -debug -debugwf -chrono -display -nothreads -out -outbin"
PTRACK2_G_OPTS_ARR=("-display" "-nothreads")
PTRACK2_G_OPTS_ARREX=("-silent" "-debug" "-debugwf" "-chrono")
PTRACK2_G_OPTS_ARROUT=("-out" "-outbin")

PTRACK2_CHI2="-i -d -w -cut -maxchi2miniter"
PTRACK2_CHI2_ARR=("-i" "-d" "-w" "-cut" "-maxchi2miniter")

PTRACK2_CHI2HD="-i -d -w -cut -maxchi2miniter -chicut -vorcut -vorsl -2filteri -2filterv"
PTRACK2_CHI2HD_ARR=("-i" "-d" "-w" "-cut" "-maxchi2miniter" "-chicut" "-vorcut" "-vorsl" "-2filteri" "-2filterv")

PTRACK2_AVAILABLE=""

#------------------------------------------
# Como tratar los parametros a partir del
# inicio de la ejecucion
#------------------------------------------
_PTrack2()
{
	local cur prev prev0 opts gopts
    COMPREPLY=()
    cur="${COMP_WORDS[COMP_CWORD]}"
    prev="${COMP_WORDS[COMP_CWORD-1]}"
    prev0="${COMP_WORDS[1]}"
    
    opts="chi2 chi2hd"
    
    if [[ "${prev}" == "PTrack2" ]]
    then
		COMPREPLY=( $(compgen -W "${opts}" -- ${cur}) )
		return 0
    fi
    
    _chi2
    
	_chi2hd
	
}

#------------------------------------------
# Como tratar los parametros si se ha
# selecionado chi2
#------------------------------------------
_chi2()
{
	local cur="${COMP_WORDS[COMP_CWORD]}"
	local prev="${COMP_WORDS[COMP_CWORD-1]}"
	local prev0="${COMP_WORDS[1]}"
    
	if [[ "${prev}" == "chi2" ]]
    then
		COMPREPLY=( $(compgen -W "${PTRACK2_CHI2} ${PTRACK2_G_OPTS}" -- ${cur}) )
		return 0
    fi
    
    PTRACK2_AVAILABLE=""
    
    _addNE2Available ${PTRACK2_CHI2_ARR[@]}
    
    _addGeneralOpts
    
    if [[ "${prev0}" == "chi2" ]]
    then
		case "${prev}" in
			"-i" | "-out" | "-outbin")
				_chi2x
				return 0
				;;
			"-d" | "-w" | "-cut" | "-maxchi2miniter")
				return 0
				;;
		esac
		COMPREPLY=( $(compgen -W "${PTRACK2_AVAILABLE}" -- ${cur}) )
		return 0
    fi
}

#------------------------------------------
# Como tratar los parametros si se ha
# selecionado chi2hd
#------------------------------------------
_chi2hd()
{
	local cur="${COMP_WORDS[COMP_CWORD]}"
	local prev="${COMP_WORDS[COMP_CWORD-1]}"
	local prev0="${COMP_WORDS[1]}"
    
	if [[ "${prev}" == "chi2hd" ]]
    then
		COMPREPLY=( $(compgen -W "${PTRACK2_CHI2HD} ${PTRACK2_G_OPTS}" -- ${cur}) )
		return 0
    fi
    
	PTRACK2_AVAILABLE=""
    
    _addNE2Available ${PTRACK2_CHI2HD_ARR[@]}
    
    _addGeneralOpts
    
    if [[ "${prev0}" == "chi2hd" ]]
    then
		case "${prev}" in
			"-i" | "-out" | "-outbin")
				_chi2x
				return 0
				;;
			"-d" | "-w" | "-cut" | "-chicut" | "-vorcut" | "-vorsl" | "-2filteri" | "-2filterv" | "-maxchi2miniter")
				return 0
				;;
		esac
		COMPREPLY=( $(compgen -W "${PTRACK2_AVAILABLE}" -- ${cur}) )
		return 0
    fi
}

#------------------------------------------
# Como tratar algunos parametros generales
#------------------------------------------
_chi2x()
{
	local cur="${COMP_WORDS[COMP_CWORD]}"
	local prev="${COMP_WORDS[COMP_CWORD-1]}"
	local prev0="${COMP_WORDS[1]}"
	
	case "${prev}" in
		"-i")
			COMPREPLY=( $(compgen -f ${cur}) )
			return 0
			;;
		"-out")
			COMPREPLY=( $(compgen -P "xysl" -S ".txt" -f ${cur}) )
			return 0
			;;
		"-outbin")
			COMPREPLY=( $(compgen -P "xysl" -f ${cur}) )
			return 0
			;;
	esac
}

#------------------------------------------
# Agrega los parametros generales disponibles
# Sin repetir y excluyentes
#------------------------------------------
_addGeneralOpts()
{
	_addNE2Available ${PTRACK2_G_OPTS_ARR[@]}
	
	_addE2Available ${PTRACK2_G_OPTS_ARREX[@]}

	_addE2Available ${PTRACK2_G_OPTS_ARROUT[@]}
}

#------------------------------------------
# Agrega los parametros no excluyentes
# que se le ingresen
#------------------------------------------
_addNE2Available()
{
	local isin
    for avl in ${*:1}
    do
		isin=0
		for word in ${COMP_WORDS[@]}
		do
			if [[ "$word" = "$avl" ]]
			then
				isin=1
			fi
		done
		
		if [[ "$isin" -eq 0 ]]
		then
			PTRACK2_AVAILABLE=$PTRACK2_AVAILABLE$avl" "
		fi
	done
}

#------------------------------------------
# Agrega los parametros excluyentes
# si existe uno en la linea de comandos
# este y todos los demas no se incluyen
#------------------------------------------
_addE2Available()
{
	local isin=0
	for avl in ${*:1}
    do
		for word in ${COMP_WORDS[@]}
		do
			if [[ "$word" = "$avl" ]]
			then
				isin=1
				break
			fi
		done
	done
	
	if [[ "$isin" -eq 0 ]]
	then
		for avl in ${*:1}
		do
			PTRACK2_AVAILABLE=$PTRACK2_AVAILABLE$avl" "
		done
	fi
}

complete -F _PTrack2 -o filenames PTrack2
