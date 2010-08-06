/***************************************************************************
 *   Copyright (C) 2005-2006 by Grup de Gràfics de Girona                  *
 *   http://iiia.udg.es/GGG/index.html?langu=uk                            *
 *                                                                         *
 *   Universitat de Girona                                                 *
 ***************************************************************************/
#ifndef UDGLOCALDATABASEPATIENTDAL_H
#define UDGLOCALDATABASEPATIENTDAL_H

#include <QList>

#include "patient.h"

namespace udg {

class DatabaseConnection;
class DicomMask;

/** Aquesta classe s'encarrega de dur a terme les operacions relacionades amb l'objecte estudi de la cache de l'aplicació.
	@author Grup de Gràfics de Girona  ( GGG ) <vismed@ima.udg.es>
*/
class LocalDatabasePatientDAL
{
public:

    LocalDatabasePatientDAL(DatabaseConnection *dbConnection);

    ///insereix el nou pacient
    void insert(Patient *newPatient);

    ///updata el pacient
    void update(Patient *patientToUpdate);

    ///Esborra els estudis pacients que compleixen amb els criteris de la màscara, només té en compte el Patient Id
    void del(const DicomMask &patientMaskToDelete);

    ///Cerca els pacients que compleixen amb els criteris de la màscara de cerca, només té en compte el Patient Id
    QList<Patient*> query(const DicomMask &patientMaskToQuery);

    ///Retorna l'estat de la última operació realitzada
    int getLastError();

private :

    DatabaseConnection *m_dbConnection;

    int m_lastSqliteError;

    ///Construeix la sentència sql per inserir el nou pacient
    QString buildSqlInsert(Patient *newPatient);

    ///Construeix la sentència updatar el pacient
    QString buildSqlUpdate(Patient *patientToUpdate);

    ///Construeix la setència per fer select de pacients a partir de la màscara, només té en compte el PatientID 
    QString buildSqlSelect(const DicomMask &patientMaskToSelect);

    ///Construeix la setència per esborrar pacients a partir de la màscara, només té en compte el Patient Id
    QString buildSqlDelete(const DicomMask &patientMaskToDelete);

    ///Emplena un l'objecte series de la fila passada per paràmetre
    Patient* fillPatient(char **reply, int row, int columns);

    ///Ens fa un ErrorLog d'una sentència sql
    void logError(const QString &sqlSentence);

};
}

#endif
