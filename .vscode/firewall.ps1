$remoteport = wsl -- cat /etc/resolv.conf `| grep nameserver
$found = $remoteport -match '\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}';

if( $found ){
  $remoteport = $matches[0];
} else{
  echo "cannot determine ip";
  exit;
}

iex "Remove-NetFireWallRule -DisplayName 'WSL 2 Firewall Unlock' ";

iex "New-NetFireWallRule -DisplayName 'WSL 2 Firewall Unlock' -Direction Inbound -LocalAddress $remoteport -Action Allow";