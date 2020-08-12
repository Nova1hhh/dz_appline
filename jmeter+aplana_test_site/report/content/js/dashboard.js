/*
   Licensed to the Apache Software Foundation (ASF) under one or more
   contributor license agreements.  See the NOTICE file distributed with
   this work for additional information regarding copyright ownership.
   The ASF licenses this file to You under the Apache License, Version 2.0
   (the "License"); you may not use this file except in compliance with
   the License.  You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
var showControllersOnly = false;
var seriesFilter = "";
var filtersOnlySampleSeries = true;

/*
 * Add header in statistics table to group metrics by category
 * format
 *
 */
function summaryTableHeader(header) {
    var newRow = header.insertRow(-1);
    newRow.className = "tablesorter-no-sort";
    var cell = document.createElement('th');
    cell.setAttribute("data-sorter", false);
    cell.colSpan = 1;
    cell.innerHTML = "Requests";
    newRow.appendChild(cell);

    cell = document.createElement('th');
    cell.setAttribute("data-sorter", false);
    cell.colSpan = 3;
    cell.innerHTML = "Executions";
    newRow.appendChild(cell);

    cell = document.createElement('th');
    cell.setAttribute("data-sorter", false);
    cell.colSpan = 7;
    cell.innerHTML = "Response Times (ms)";
    newRow.appendChild(cell);

    cell = document.createElement('th');
    cell.setAttribute("data-sorter", false);
    cell.colSpan = 1;
    cell.innerHTML = "Throughput";
    newRow.appendChild(cell);

    cell = document.createElement('th');
    cell.setAttribute("data-sorter", false);
    cell.colSpan = 2;
    cell.innerHTML = "Network (KB/sec)";
    newRow.appendChild(cell);
}

/*
 * Populates the table identified by id parameter with the specified data and
 * format
 *
 */
function createTable(table, info, formatter, defaultSorts, seriesIndex, headerCreator) {
    var tableRef = table[0];

    // Create header and populate it with data.titles array
    var header = tableRef.createTHead();

    // Call callback is available
    if(headerCreator) {
        headerCreator(header);
    }

    var newRow = header.insertRow(-1);
    for (var index = 0; index < info.titles.length; index++) {
        var cell = document.createElement('th');
        cell.innerHTML = info.titles[index];
        newRow.appendChild(cell);
    }

    var tBody;

    // Create overall body if defined
    if(info.overall){
        tBody = document.createElement('tbody');
        tBody.className = "tablesorter-no-sort";
        tableRef.appendChild(tBody);
        var newRow = tBody.insertRow(-1);
        var data = info.overall.data;
        for(var index=0;index < data.length; index++){
            var cell = newRow.insertCell(-1);
            cell.innerHTML = formatter ? formatter(index, data[index]): data[index];
        }
    }

    // Create regular body
    tBody = document.createElement('tbody');
    tableRef.appendChild(tBody);

    var regexp;
    if(seriesFilter) {
        regexp = new RegExp(seriesFilter, 'i');
    }
    // Populate body with data.items array
    for(var index=0; index < info.items.length; index++){
        var item = info.items[index];
        if((!regexp || filtersOnlySampleSeries && !info.supportsControllersDiscrimination || regexp.test(item.data[seriesIndex]))
                &&
                (!showControllersOnly || !info.supportsControllersDiscrimination || item.isController)){
            if(item.data.length > 0) {
                var newRow = tBody.insertRow(-1);
                for(var col=0; col < item.data.length; col++){
                    var cell = newRow.insertCell(-1);
                    cell.innerHTML = formatter ? formatter(col, item.data[col]) : item.data[col];
                }
            }
        }
    }

    // Add support of columns sort
    table.tablesorter({sortList : defaultSorts});
}

$(document).ready(function() {

    // Customize table sorter default options
    $.extend( $.tablesorter.defaults, {
        theme: 'blue',
        cssInfoBlock: "tablesorter-no-sort",
        widthFixed: true,
        widgets: ['zebra']
    });

    var data = {"OkPercent": 98.2706924203333, "KoPercent": 1.72930757966669};
    var dataset = [
        {
            "label" : "KO",
            "data" : data.KoPercent,
            "color" : "#FF6347"
        },
        {
            "label" : "OK",
            "data" : data.OkPercent,
            "color" : "#9ACD32"
        }];
    $.plot($("#flot-requests-summary"), dataset, {
        series : {
            pie : {
                show : true,
                radius : 1,
                label : {
                    show : true,
                    radius : 3 / 4,
                    formatter : function(label, series) {
                        return '<div style="font-size:8pt;text-align:center;padding:2px;color:white;">'
                            + label
                            + '<br/>'
                            + Math.round10(series.percent, -2)
                            + '%</div>';
                    },
                    background : {
                        opacity : 0.5,
                        color : '#000'
                    }
                }
            }
        },
        legend : {
            show : true
        }
    });

    // Creates APDEX table
    createTable($("#apdexTable"), {"supportsControllersDiscrimination": true, "overall": {"data": [0.982706924203333, 500, 1500, "Total"], "isController": false}, "titles": ["Apdex", "T (Toleration threshold)", "F (Frustration threshold)", "Label"], "items": [{"data": [1.0, 500, 1500, "go_to_clients"], "isController": false}, {"data": [1.0, 500, 1500, "pacing"], "isController": false}, {"data": [1.0, 500, 1500, "open_site"], "isController": false}, {"data": [1.0, 500, 1500, "JDBC Request (TRUNCATE)"], "isController": false}, {"data": [1.0, 500, 1500, "go_to_guestBook_1"], "isController": false}, {"data": [0.9514508928571429, 500, 1500, "send_comment_1"], "isController": false}, {"data": [1.0, 500, 1500, "go_to_guestBook_2"], "isController": false}, {"data": [0.91015625, 500, 1500, "send_comment_2"], "isController": false}, {"data": [1.0, 500, 1500, "choose_client"], "isController": false}]}, function(index, item){
        switch(index){
            case 0:
                item = item.toFixed(3);
                break;
            case 1:
            case 2:
                item = formatDuration(item);
                break;
        }
        return item;
    }, [[0, 0]], 3);

    // Create statistics table
    createTable($("#statisticsTable"), {"supportsControllersDiscrimination": true, "overall": {"data": ["Total", 14341, 248, 1.72930757966669, 5.709573948818081, 0, 125, 2.0, 18.0, 34.0, 46.0, 47.73062368325584, 873.2196684186506, 15.577614501617536], "isController": false}, "titles": ["Label", "#Samples", "KO", "Error %", "Average", "Min", "Max", "Median", "90th pct", "95th pct", "99th pct", "Transactions\/s", "Received", "Sent"], "items": [{"data": ["go_to_clients", 1792, 0, 0.0, 1.9419642857142838, 1, 10, 2.0, 2.0, 3.0, 3.0699999999999363, 5.966392430139605, 35.74610091614255, 2.214090940872119], "isController": false}, {"data": ["pacing", 1793, 0, 0.0, 0.02175125488008928, 0, 1, 0.0, 0.0, 0.0, 1.0, 5.969602636879692, 3.7385740675617183, 0.0], "isController": false}, {"data": ["open_site", 1793, 0, 0.0, 2.357501394311211, 1, 13, 2.0, 3.0, 3.0, 4.0, 5.969642387457426, 132.1449326396773, 1.9531445082952392], "isController": false}, {"data": ["JDBC Request (TRUNCATE)", 1, 0, 0.0, 13.0, 13, 13, 13.0, 13.0, 13.0, 13.0, 76.92307692307693, 0.6760817307692308, 0.0], "isController": false}, {"data": ["go_to_guestBook_1", 1793, 0, 0.0, 1.8778583379810372, 1, 7, 2.0, 2.0, 2.0, 3.0, 5.969642387457426, 23.971968764670237, 2.2969066814714685], "isController": false}, {"data": ["send_comment_1", 1792, 87, 4.854910714285714, 1.7120535714285703, 0, 32, 1.0, 3.0, 4.0, 8.0, 5.966551353295088, 1.8422614315894266, 3.3615013590801786], "isController": false}, {"data": ["go_to_guestBook_2", 1793, 0, 0.0, 18.423870607919685, 0, 125, 14.0, 43.0, 46.0, 56.0, 5.9687878666826455, 320.05018999920105, 1.7370105315150668], "isController": false}, {"data": ["send_comment_2", 1792, 161, 8.984375, 17.45535714285714, 0, 81, 13.0, 42.0, 45.0, 55.0, 5.965677380694775, 320.2017014362818, 1.736105331491253], "isController": false}, {"data": ["choose_client", 1792, 0, 0.0, 1.8822544642857142, 1, 5, 2.0, 2.0, 2.0, 3.0, 5.966432160134778, 35.74757449820541, 2.284024811301595], "isController": false}]}, function(index, item){
        switch(index){
            // Errors pct
            case 3:
                item = item.toFixed(2) + '%';
                break;
            // Mean
            case 4:
            // Mean
            case 7:
            // Median
            case 8:
            // Percentile 1
            case 9:
            // Percentile 2
            case 10:
            // Percentile 3
            case 11:
            // Throughput
            case 12:
            // Kbytes/s
            case 13:
            // Sent Kbytes/s
                item = item.toFixed(2);
                break;
        }
        return item;
    }, [[0, 0]], 0, summaryTableHeader);

    // Create error table
    createTable($("#errorsTable"), {"supportsControllersDiscrimination": false, "titles": ["Type of error", "Number of errors", "% in errors", "% in all samples"], "items": [{"data": ["\\u041D\\u0435 \\u043D\\u0430\\u0439\\u0434\\u0435\\u043D \\u043A\\u043E\\u043C\\u043C\\u0435\\u043D\\u0442\\u0430\\u0440\\u0438\\u0439 \\u0432 response", 161, 64.91935483870968, 1.1226553238965205], "isController": false}, {"data": ["500", 87, 35.08064516129032, 0.6066522557701695], "isController": false}]}, function(index, item){
        switch(index){
            case 2:
            case 3:
                item = item.toFixed(2) + '%';
                break;
        }
        return item;
    }, [[1, 1]]);

        // Create top5 errors by sampler
    createTable($("#top5ErrorsBySamplerTable"), {"supportsControllersDiscrimination": false, "overall": {"data": ["Total", 14341, 248, "\\u041D\\u0435 \\u043D\\u0430\\u0439\\u0434\\u0435\\u043D \\u043A\\u043E\\u043C\\u043C\\u0435\\u043D\\u0442\\u0430\\u0440\\u0438\\u0439 \\u0432 response", 161, "500", 87, null, null, null, null, null, null], "isController": false}, "titles": ["Sample", "#Samples", "#Errors", "Error", "#Errors", "Error", "#Errors", "Error", "#Errors", "Error", "#Errors", "Error", "#Errors"], "items": [{"data": [], "isController": false}, {"data": [], "isController": false}, {"data": [], "isController": false}, {"data": [], "isController": false}, {"data": [], "isController": false}, {"data": ["send_comment_1", 1792, 87, "500", 87, null, null, null, null, null, null, null, null], "isController": false}, {"data": [], "isController": false}, {"data": ["send_comment_2", 1792, 161, "\\u041D\\u0435 \\u043D\\u0430\\u0439\\u0434\\u0435\\u043D \\u043A\\u043E\\u043C\\u043C\\u0435\\u043D\\u0442\\u0430\\u0440\\u0438\\u0439 \\u0432 response", 161, null, null, null, null, null, null, null, null], "isController": false}, {"data": [], "isController": false}]}, function(index, item){
        return item;
    }, [[0, 0]], 0);

});
