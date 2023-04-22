#!/bin/bash

result(){


  var=$?

  if [ $var -eq 0 ]
  then
    echo "Good" >> ../test/Result.txt
  else
    echo "Bad" >> ../test/Result.txt
  fi
}


cd ../test/good
fichiers_good=`ls`
chemin_good=../test/good

cd ../syn-err
fichiers_err=`ls`
chemin_err=../test/syn-err

cd ../sem-err
fichiers_sem_err=`ls`
chemin_sem_err=../test/sem-err

cd ../warn
fichiers_warn=`ls`
chemin_warn=../test/warn


cd ../../bin

exec=tpcas


# Traitement des fichier du dossier des scripts tests corrects
echo -e "Result of the tests" > ../test/Result.txt

echo -e >> ../test/Result.txt
echo -e "===================== CORRECTS ====================" >> ../test/Result.txt
echo -e >> ../test/Result.txt

for i in $fichiers_good
  do

    echo "Fichier : $i" >> ../test/Result.txt

    commande=$(./tpcc $chemin_good/$i 2>&1)
    var=$?

    if [ $var -eq 0 ]
    then
      echo "Good" >> ../test/Result.txt
    else

      if [ $var -eq 1 ]
      then
        echo "Bad (syntaxical error)" >> ../test/Result.txt
      else

        if [ $var -eq 2 ]
        then
          echo "Bad (semantical error)" >> ../test/Result.txt
        else
          echo "Bad (extern error (memory error, segfault error...))" >> ../test/Result.txt

        fi

      fi

    fi

    echo -e "" >> ../test/Result.txt
  done



# Traitement des fichier du dossier des scripts tests syntaxiquement incorrects
echo -e >> ../test/Result.txt
echo -e "==================== ERREURS SYNTAXIQUES ====================" >> ../test/Result.txt
echo -e >> ../test/Result.txt

for i in $fichiers_err
  do

    echo "Fichier : $i" >> ../test/Result.txt

    commande=$(./tpcc $chemin_err/$i 2>&1)
    var=$?

    if [ $var -eq 0 ]
    then
      echo "Good" >> ../test/Result.txt
    else
      if [ $var -eq 1 ]
      then
        echo "Bad (syntaxical error)" >> ../test/Result.txt
      else

        if [ $var -eq 2 ]
        then
          echo "Bad (semantical error)" >> ../test/Result.txt
        else
          echo "Bad (extern error (memory error, segfault error...))" >> ../test/Result.txt

        fi

      fi
    fi

    echo -e "" >> ../test/Result.txt
  done



# Traitement des fichier du dossier des scripts tests semantiquement incorrects
echo -e >> ../test/Result.txt
echo -e "==================== ERREURS SEMANTIQUES ====================" >> ../test/Result.txt
echo -e >> ../test/Result.txt

for i in $fichiers_sem_err
  do

    echo "Fichier : $i" >> ../test/Result.txt

    commande=$(./tpcc $chemin_sem_err/$i 2>&1)
    var=$?

    if [ $var -eq 0 ]
    then
      echo "Good" >> ../test/Result.txt
    else
      if [ $var -eq 1 ]
      then
        echo "Bad (syntaxical error)" >> ../test/Result.txt
      else

        if [ $var -eq 2 ]
        then
          echo "Bad (semantical error)" >> ../test/Result.txt
        else
          echo "Bad (extern error (memory error, segfault error...))" >> ../test/Result.txt

        fi

      fi
    fi

    echo -e "" >> ../test/Result.txt
  done





# Traitement des fichier du dossier des scripts tests provoquant des warnings
echo -e >> ../test/Result.txt
echo -e "==================== WARNINGS ====================" >> ../test/Result.txt
echo -e >> ../test/Result.txt

for i in $fichiers_warn
  do

    echo "Fichier : $i" >> ../test/Result.txt

    commande=$(./tpcc $chemin_warn/$i 2>&1)
    var=$?

    if [ $var -eq 0 ]
    then
      echo "Good" >> ../test/Result.txt
    else
      if [ $var -eq 1 ]
      then
        echo "Bad (syntaxical error)" >> ../test/Result.txt
      else

        if [ $var -eq 2 ]
        then
          echo "Bad (semantical error)" >> ../test/Result.txt
        else
          echo "Bad (extern error (memory error, segfault error...))" >> ../test/Result.txt

        fi

      fi
    fi

    echo -e "" >> ../test/Result.txt
  done



#— 0 si le programme source ne contient aucune erreur (même s’il y a des avertissements)
#— 1 s’il contient une erreur lexicale ou syntaxique (5)
#— 2 s’il contient une erreur sémantique (6)
#— 3 ou plus pour les autres sortes d’erreurs : ligne de commande, fonctionnalité non implémentée,
#mémoire insuffisante...