<p align="center">
    <img src="image/logo.png", alt ="Crypto$crapper">
</p><br/>

A minimalist CLI tool to fetch the price of cryptocurrency with web scraping from https://coinmarketcap.com/.
Note: Prices may be delayed. 

## usage
To compile the file, do
```bash
make
```
To execute the file, do
```bash
CryptoScrapper (code) (-option)
```

Note: for supported cryptocurrencies, both full-name and the code can be used. 
## Option

- -o: Display only the price without any formatting 
- -$: Display price in USD.
- -v: Show price and 24-hour variation of the cryptocurrencies.



## Crypto supported
Here's the list of all cryptocurrency with custom support and logo. For others, only urls name in coinmarketcap.com will works.

| Crypto | Code | 
|----------|----------|
| Bitcoin  | btc   | 
| Etheruem  | eth |
| Solana   | sol   | 
| XRP   | xrp   | 
| Dogecoin   | doge   | 

Otherwise a default-logo will be used. 
