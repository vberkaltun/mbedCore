get-childitem -Recurse *.* | foreach { rename-item $_ $_.Name.Replace("hukseflux", "") }