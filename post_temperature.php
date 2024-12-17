<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $temperature = $_POST['temperature'];
    $logFilePath = __DIR__ . "/temperature_log.txt";
    
    $log = "Sıcaklık: " . $temperature . "°C\n";
    if (file_put_contents($logFilePath, $log, FILE_APPEND)) {
        echo "Veri alındı: $temperature °C";
    } else {
        echo "Hata!";
    }
} else {
    echo "POST isteği gönderiniz.";
}
?>
