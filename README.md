# SMCloro
Nos sistemas de tratamento de água, as etapas de desinfeção são essenciais para garantir que a água esteja livre de microrganismos associados a doenças transmitidas pela água. A cloração é o método mais antigo e mais utilizado devido à sua disponibilidade, baixo custo e efeitos residuais. Aplicado em concentrações não prejudiciais ao homem, é eficaz e protege os sistemas de distribuição de água. Neste artigo científico, são abordados os problemas encontrados no monitoramento e controle da cloração que dependem inteiramente da intervenção humana. Além disso, propõe-se desenvolver um protótipo de sistema baseado em IoT para monitoramento remoto e controle de tratamento direto de água doméstica.


![image](https://user-images.githubusercontent.com/48352481/182041346-ad632b62-ce4e-45bf-b7d9-6cd8685608bc.png)

A figura demonstra a arquitetura do sistema proposto consiste na comunicação entre o Lolin D1 Mini Pro e o Arduino UNO.  Escolha esta, feita, devido a existência de apenas uma porta analógica no Lolin D1 Mini Pro, onde temos o suporte ao wi-fi.   Os dados são coletados dos sensores de temperatura, pH e de nível da água pelo Arduino Uno e são enviados pela porta serial para o Lolin D1 Mini Pro, onde são recebidas no Blynk.
