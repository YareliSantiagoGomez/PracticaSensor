<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "sensor_db";

// Conectar Reynaldo modifique conn
$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Error de conexión: " . $conn->connect_error);
}

// Obtener el último registro
$sql = "SELECT temperatura, humedad FROM datos_sensor ORDER BY id DESC LIMIT 1";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    echo json_encode($result->fetch_assoc());
} else {
    echo json_encode(["temperatura" => "N/A", "humedad" => "N/A"]);
}

$conn->close();
?>
