import sys
import string
import re

class TigerCodeGenDecoder(object):
    """description of class"""
    def TranslateSchemaIntoCode(self, schemaData):
        schema = schemaData.strip('\n\r')

        pattern = re.compile(r'([\w]+)@(\w+)')

        pattern2 = re.compile(r'\{(.*?)\}')
        
        
        result2 = pattern2.findall(schema.replace('\t', ''))
        result = pattern.findall(schema)

        return result, result2


    def BasicDataTypeConvertor(self, typeLower):

        UE4Type = 'InvalidType'

        if(typeLower == 'bool'):
            UE4Type = 'bool'
        elif(typeLower == 'int32' or typeLower == 'int'):
            UE4Type = 'int32'
        elif(typeLower == 'vector3'):
            UE4Type = 'FVector'
        elif(typeLower == 'float'):
            UE4Type = 'float'
        elif(typeLower == 'string'):
            UE4Type == 'FString'
        elif(typeLower == 'transform'):
            UE4Type == 'FTransform'

        return UE4Type


    # convert regular data type string to type string
    def GenerateDataTypeString(self, name, type):

        typeLower = type.lower()
        isList = 'list' in str(type.lower())
        UE4Type = ''

        if isList:
            pattern = re.compile(r'\<(.*?)\>')
            insideDataType = pattern.findall(typeLower)

            UE4Type = 'TArray<' + self.BasicDataTypeConvertor(insideDataType[0]) + '>'
        else:
            UE4Type = self.BasicDataTypeConvertor(typeLower)

        return UE4Type + ' ' + name + ';'

        
    def GenerateCPlusPlusCode(self, compList, dataList, path):

        codes = []
        compNames = []

        dataLen = len(compList)
        count = 0

        while(count < dataLen):
            name = compList[count][1];
            fileDirPath =path + "/" + name + "Component.h"           
            compNames.append(fileDirPath)

            # ok we remove last index becuase it has nothing from spliting ";"
            dataDeclares = dataList[count].split(';')
            dataDeclares.pop()

            dataDeclareCodes = 'public:\n'

            codestart = '''#pragma once\n#include "CoreMinimal.h"\n#include "ECS_Component.h"\n''' 
            codestart += '''#include "''' + name + '''Component.generated.h"\nUCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))\n'''
            codestart += '''class TSECSFRAMEWORK_API U''' + name + '''Component : public UECS_Component\n{\n\tGENERATED_BODY();\n'''

            for i in dataDeclares :
                dataTypes = i.split(':')
                dataDeclareCodes += '\tUPROPERTY(BlueprintReadWrite)\n\t' + self.GenerateDataTypeString(dataTypes[1], dataTypes[0]) + '\n'

            codeend = '''};'''

            code = codestart + dataDeclareCodes + codeend

            codes.append(code)

            # increment
            count +=1


       
        return codes, compNames

   