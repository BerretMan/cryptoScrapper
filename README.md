# cryptoScrapper
A minimalist cli to get the price of some crypto.
The program use web scrapping on https://coinmarketcap.com/ and can be late on price (I'm not responsable for spread)
## usage
To compile the file, do
```bash
make
```
To execute the file, do
```bash
CryptoScrapper (code) (-option)
```
## Option

- -o: show only the value without any artifice 
- -$: show price in USD.
- -v: add variation of price in 1 day 



## Crypto supported
Currently, only 4 cryptos have custom logo
| Crypto | Code | 
|----------|----------|
| Bitcoin  | btc   | 
| Etheruem  | eth |
| Solana   | sol   | 
| Dogecoin   | doge   | 

Otherwise will have default logo
