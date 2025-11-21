#!/bin/bash

# Script para generar datos de prueba para el sistema de nómina
# 20 registros de empleados de ejemplo

ARCHIVO_DATOS="empleados.txt"

print_message() {
    echo -e "\033[0;32m[INFO]\033[0m $1"
}

print_step() {
    echo -e "\033[0;34m>>>\033[0m $1"
}

# Verificar si el archivo ya existe
if [ -f "$ARCHIVO_DATOS" ]; then
    print_message "El archivo $ARCHIVO_DATOS ya existe"
    read -p "¿Desea sobrescribirlo? (y/n): " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        echo "Operación cancelada."
        exit 0
    fi
    # Hacer backup del archivo existente
    cp "$ARCHIVO_DATOS" "$ARCHIVO_DATOS.backup"
    print_message "Backup creado: $ARCHIVO_DATOS.backup"
fi

print_step "Generando base de datos de prueba con 20 empleados..."

# Crear archivo de datos con 20 registros de ejemplo
cat > "$ARCHIVO_DATOS" << 'EOF'
1,Juan,Pérez,Gerente,45.50,40.0,1820.00,2023-01-15
2,María,García,Contadora,35.75,42.5,1519.38,2023-02-20
3,Carlos,Rodríguez,Desarrollador,38.25,45.0,1721.25,2023-03-10
4,Ana,Martínez,Diseñadora,32.00,38.0,1216.00,2023-01-30
5,Luis,Hernández,Analista,36.50,40.0,1460.00,2023-04-05
6,Laura,López,Recursos Humanos,28.75,35.0,1006.25,2023-05-12
7,Pedro,González,Técnico,30.25,44.0,1331.00,2023-02-28
8,Isabel,Díaz,Marketing,33.00,37.5,1237.50,2023-03-22
9,Ricardo,Morales,Desarrollador,39.50,42.0,1659.00,2023-06-18
10,Elena,Castro,Supervisora,34.25,40.0,1370.00,2023-04-30
11,Jorge,Ruiz,Soporte Técnico,29.50,36.0,1062.00,2023-07-10
12,Mónica,Vargas,Asistente,26.80,32.5,871.00,2023-05-25
13,Fernando,Silva,Ingeniero,41.00,41.0,1681.00,2023-08-15
14,Gabriela,Rojas,Consultora,37.25,39.0,1452.75,2023-06-05
15,Diego,Mendoza,Auditor,35.00,38.5,1347.50,2023-09-20
16,Patricia,Guerrero,Coordinadora,31.50,36.0,1134.00,2023-07-30
17,Roberto,Ortiz,Especialista,36.75,43.0,1580.25,2023-10-12
18,Claudia,Ramírez,Investigadora,34.50,37.0,1276.50,2023-08-25
19,Sergio,Flores,Administrador,32.25,35.5,1144.88,2023-11-05
20,Adriana,Vega,Planificadora,33.75,40.0,1350.00,2023-09-15
EOF

print_message "Base de datos creada exitosamente: $ARCHIVO_DATOS"
print_message "Total de registros generados: 20"

# Mostrar contenido del archivo
print_step "Mostrando los primeros 5 registros:"
echo ""
head -n 5 "$ARCHIVO_DATOS"
echo ""
print_message "¡Base de datos lista para usar!"
