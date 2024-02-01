#!/bin/bash


INTERVALO_TEMPO=$1
CAMINHHO_ARQ=$2
LIM_CPU=$3
TOKEN=$4
ID=$5


# Inicializando variáveis
CONTADOR=0 					# para contar 100 medições
SOMA_CPU_OCIOSA=0 			# para fazer a média das 100 medições
SOMA_VEZES_SEM_CONEXAO=0 	# para calcular o tempo sem conexão





if [ -z "$1" -o -z "$2" -o -z "$3" -o -z "$4" -o -z "$5" ]; then
	echo "O programa deve ser executado da forma: ./ep2.sh <intervalo de tempo> <caminho para salvar as verificações> <porcentagem de CPU> <token do bot> <id do bot>"
	echo aborted
	exit 0
fi

# Mensagem de início de nova execucão para o bot
curl -s --data "text=########################
O PROGRAMA FOI EXECUTADO
                 $( date +%d/%m/%Y )
             NOVA MEDIÇÃO
########################" https://api.telegram.org/bot${TOKEN}/sendMessage?chat_id=${ID} 1>/dev/null

# Mensagem de início de nova execução no arquivo
cd ~
echo "

" >> ${CAMINHHO_ARQ}
echo "=======================================
O PROGRAMA FOI EXECUTADO - NOVA MEDIÇÃO
              $( date +%d/%m/%Y )
=======================================" >> ${CAMINHHO_ARQ}
echo "" >> ${CAMINHHO_ARQ}





# EXECUÇÃO DO PROGRAMA
while [ 1 ]; do

	DATA=$( date +%d/%m/%Y )
	HORA=$( date +%H:%M )

	cd ~
	IPS_CONECTADOS=$(netstat -anp 2>/dev/null | grep 45052 | grep ESTABELECIDA | awk '{print $5}' | awk 'BEGIN{FS=":"} {print $1}' | uniq)
	CPU_OCIOSA=$( top -n 1 | grep "CPU(s)" | cut -d ',' -f 7,8 | cut  -d ' ' -f 2 )





	# CONSTRUINDO A MENSAGEM QUE SERÁ IMPRESSA NA SAÍDA PADRÃO E QUE O BOT DO TELEGRAM IRÁ ENVIAR
	# data e hora
	MENSAGEM="Data: ${DATA}  //  Hora: ${HORA}
	"

	# ips conectados, se houverem
	if [ $(netstat -anp 2>/dev/null | grep 45052 | grep ESTABELECIDA | awk '{print $5}' | awk 'BEGIN{FS=":"} {print $1}' | uniq -c | cut -b 7) -gt 0 2>/dev/null ]; then
		# quando não há nenhum IP conectado, não existe nada para ser comparado, então esse erro vai para /dev/null
		MENSAGEM="${MENSAGEM}IPs conectados: ${IPS_CONECTADOS}
	"
	fi

	# cpu ociosa
	if [ $( echo "${CPU_OCIOSA} < ${LIM_CPU}" | tr ',' '.' | cut -d '%' -f 1 | bc -l ) -eq 1 ]; then
		# com o tr e o cut, é possível digitar a porcentagem com vírgula ou ponto, e com o símbolo '%' ou sem
		MENSAGEM="${MENSAGEM}Porcentagem de CPU ociosa: ${CPU_OCIOSA}%
	"
	fi

	# conexão com o servidor
	if [ $( netstat -anp 2>/dev/null | grep 45052 | grep OUÇA | uniq -c | cut -b 7) -eq 1 2>/dev/null ]; then
		# quando não há conexão estabelecida, não existe nada para ser comparado, então esse erro vai para /dev/null
		MENSAGEM="${MENSAGEM}O servidor está conectado"
	else 
		MENSAGEM="${MENSAGEM}O servidor está fora do ar"
		SOMA_VEZES_SEM_CONEXAO=$( echo "${SOMA_VEZES_SEM_CONEXAO} + 1" | bc -l )
	fi





	# O QUE SERÁ IMPRESSO NA SAÍDA PADRÃO E PELO BOT:
	echo "-------------------------------------------------
	${MENSAGEM}"
	curl -s --data "text=${MENSAGEM}" https://api.telegram.org/bot${TOKEN}/sendMessage?chat_id=${ID} 1>/dev/null





	# O QUE SERÁ SALVO NO ARQUIVO:
	cd ~

	echo "Data: ${DATA}  //  Hora: ${HORA}" >> ${CAMINHHO_ARQ}

	echo "Porcentagem de CPU ociosa: ${CPU_OCIOSA}%" >> ${CAMINHHO_ARQ}

	if [ $( netstat -anp 2>/dev/null | grep 45052 | grep ESTABELECIDA | cut -b 21-29 | uniq -c | cut -b 7 ) -gt 0 2>/dev/null ]; then
		# quando não há nenhum IP conectado, não existe nada para ser comparado, então esse erro vai para /dev/null
		echo "IPs conectados: ${IPS_CONECTADOS}" >> ${CAMINHHO_ARQ}
	fi

	if [ $( netstat -anp 2>/dev/null | grep 45052 | grep OUÇA | uniq -c | cut -b 7) -eq 1 2>/dev/null ]; then
		# quando não há conexão estabelecida, não existe nada para ser comparado, então esse erro vai para /dev/null
		echo "O servidor está conectado" >> ${CAMINHHO_ARQ}
	else 
		echo "O servidor está fora do ar" >> ${CAMINHHO_ARQ}
	fi

	echo "" >> ${CAMINHHO_ARQ}



	SOMA_CPU_OCIOSA=$( echo "${SOMA_CPU_OCIOSA} + ${CPU_OCIOSA}" | tr ',' '.' | bc -l )

	CONTADOR=$( echo "${CONTADOR} + 1" | bc )

	# A cada 100 medições:
	if [ "${CONTADOR}" -eq '100' ]; then
		# no tempo em que o servidor fica fora do ar, são adicionados 1,2 segundos para cada medição, pois há um delay de 1,2 segundos para fazê-las
		echo "
		" >> ${CAMINHHO_ARQ}
		echo "###############################################################################" >> ${CAMINHHO_ARQ}
		echo "" >> ${CAMINHHO_ARQ}
		echo "MÈDIA DAS 100 ÚLTIMAS MEDIÇÕES DE OCIOSIDADE DE CPU: $( echo "${SOMA_CPU_OCIOSA} / 100" | bc -l | cut -b 1-5 | tr '.' ',')%" >> ${CAMINHHO_ARQ}
		echo "TEMPO EM QUE O SERVIDOR FICOU FORA DO AR NAS ÚLTIMAS 100 MEDIÇÕES: $( echo "${SOMA_VEZES_SEM_CONEXAO} * (${INTERVALO_TEMPO} + 1.2)" | bc -l ) segundos" >> ${CAMINHHO_ARQ}
		echo "" >> ${CAMINHHO_ARQ}
		echo "###############################################################################" >> ${CAMINHHO_ARQ}
		echo " 
		" >> ${CAMINHHO_ARQ}
		CONTADOR=0
		SOMA_CPU_OCIOSA=0
		SOMA_VEZES_SEM_CONEXAO=0
	fi





	sleep ${INTERVALO_TEMPO}s

done 




exit 0