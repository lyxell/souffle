#include <string>

namespace souffle {
namespace profile {
namespace html {
std::string htmlHeadTop = R"___(
<!--
* Souffle - A Datalog Compiler
* Copyright (c) 2017, The Souffle Developers. All rights reserved
* Licensed under the Universal Permissive License v 1.0 as shown at:
* - https://opensource.org/licenses/UPL
* - <souffle root>/licenses/SOUFFLE-UPL.txt
-->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Souffle Profiler</title>
)___";
std::string htmlHeadBottom = R"___(
</head>
)___";

std::string htmlBodyTop = R"___(
<body>
<div id="wrapper" style="width:100%;height:inherit;">
    <ul class="tab">
        <li><a href="javascript:void(0)" class="tablinks" id="default" onclick="changeTab(event, 'Top');">Top</a></li>
        <li><a href="javascript:void(0)" class="tablinks" id="rel_tab" onclick="changeTab(event, 'Relations');came_from = 'rel';">Relations</a></li>
        <li><a href="javascript:void(0)" class="tablinks" id="rul_tab" onclick="changeTab(event, 'Rules');came_from = 'rul';">Rules</a></li>
        <li><a href="javascript:void(0)" class="tablinks" onclick="changeTab(event, 'Help')">Help</a></li>
        <li id="chart-tab" style="display:none;"><a href="javascript:void(0)" id="chart_tab" onclick="changeTab(event, 'Chart')" class="tablinks">Chart</a></li>
        <li id="code-tab" style="display:none;"><a href="javascript:void(0)" id="code_tab" onclick="changeTab(event, 'Code')" class="tablinks">Code</a></li>
    </ul>
    <div id="Help" class="tabcontent" style="max-width:800px;margin-left: auto;margin-right: auto;">
        <h3>GUI Souffle profiler</h3>
        <p>Select Relation or Rules from the top bar to see a table of Relations or Rules</p>
        <p>Tables show:</p>
        <ul>
            <li>Name/description</li>
            <li>ID(generated by profiler)</li>
            <li>Total time the rule/relation was being processed</li>
            <li>Non-recursive time</li>
            <li>Recursive time</li>
            <li>Copy time</li>
            <li>number of Tuples of the Rule/relation</li>
            <li>Percentage of time the rule/relation ran in comparison to the total</li>
            <li>Percentage of tuples generated by the rule/relation compared to the total</li>
            <li>The source location of the rule/relation in the datalog file</li>
        </ul>
        <p>The tables are sortable by all columns by clicking on the header. Number precision can be toggled by pressing the button at the top of the page to show either shorthand or full precision.</p>
        <p>In the relation tab, to see the rules of a relation, select a relation from the table, and a table of rules will appear below. Similary, by selecting a Rule in the Rule tab, a list of versions of the rule will show up (for recursive rules).</p>
        <p>To visualise a graph of a relation, select the relation from the Relations table, then press the graph selected button to show the iterations of the Relation</p>
        <p>Similarly for a Rule, in the Rules table, select a rule, and select either graph the selected rule's iterations or the versions of the selected rule.</p>
    </div>
    <div id="Top" class="tabcontent" style="max-width:800px;margin-left: auto;margin-right: auto;">
        <h3>Top</h3>
    </div>
    <div id="Relations" class="tabcontent">
        <h3>Relations table</h3>
        <button onclick="toggle_precision();">Toggle number precision</button>
        <button onclick="graphRel();">Graph iterations of selected</button>
    <div class="table_wrapper">
        <table id='Rel_table'>
            <thead>
            <tr>
                <th data-sort-method="text">Name</th>
                <th data-sort-method="text">ID</th>
                <th data-sort-method="time">Total Time</th>
                <th data-sort-method="time">Non Rec Time</th>
                <th data-sort-method="time">Rec Time</th>
                <th data-sort-method="time">Copy Time</th>
                <th data-sort-method="number">Tuples</th>
                <th data-sort-method="number">% of Time</th>
                <th data-sort-method="number">% of Tuples</th>
                <th data-sort-method="text">Source</th>
            </tr>
            </thead>
            <tbody id="Rel_table_body">
            </tbody>
        </table>
    </div>
    <hr/>
    <div id="rulesofrel" style="display:none;">
        <h3>Rules of Relation</h3>
        <div class="table_wrapper">
            <table id="rulesofrel_table">
                <thead>
                <tr>
                    <th data-sort-method="text" style="width:80%;">Name</th>
                    <th data-sort-method="text">ID</th>
                    <th data-sort-method="time">Total Time</th>
                    <th data-sort-method="time">Non Rec Time</th>
                    <th data-sort-method="time">Rec Time</th>
                    <th data-sort-method="time">Copy Time</th>
                    <th data-sort-method="number">Tuples</th>
                    <th data-sort-method="number">% of Time</th>
                    <th data-sort-method="number">% of Tuples</th>
                    <th data-sort-method="text" style="width:20%;">Source</th>
                </tr>
                </thead>
                <tbody id="rulesofrel_body">

                </tbody>
            </table>
        </div>
    </div>
</div>
<div id="Rules" class="tabcontent">
    <h3>Rules table</h3>
    <button onclick="toggle_precision();">Toggle number precision</button>
    <button onclick="graphIterRul();">Graph iterations of selected</button>
    <button onclick="graphRulVer();">Graph versions of selected</button>
    <div class="table_wrapper">
        <table id='Rul_table'>
            <thead>
            <tr>
                <th data-sort-method="text">Name</th>
                <th data-sort-method="text">ID</th>
                <th data-sort-method="time">Total Time</th>
                <th data-sort-method="time">Non Rec Time</th>
                <th data-sort-method="time">Rec Time</th>
                <th data-sort-method="time">Copy Time</th>
                <th data-sort-method="number">Tuples</th>
                <th data-sort-method="number">% of Time</th>
                <th data-sort-method="number">% of Tuples</th>
                <th data-sort-method="text">Source</th>
            </tr>
            </thead>
            <tbody id="Rul_table_body">
            </tbody>
        </table>
    </div>
    <hr/>
    <div id="rulver" style="display:none;">
        <h3>Rule Versions Table</h3>
        <div class="table_wrapper">
            <table id='rulvertable'>
                <thead>
                <tr>
                    <th data-sort-method="text">Name</th>
                    <th data-sort-method="text">ID</th>
                    <th data-sort-method="time">Total Time</th>
                    <th data-sort-method="time">Non Rec Time</th>
                    <th data-sort-method="time">Rec Time</th>
                    <th data-sort-method="time">Copy Time</th>
                    <th data-sort-method="number">Tuples</th>
                    <th data-sort-method="number">Ver</th>
                    <th data-sort-method="number">% of Time</th>
                    <th data-sort-method="number">% of Tuples</th>
                    <th data-sort-method="text">Source</th>
                </tr>
                </thead>
                <tbody id="rulver_body">
                </tbody>
            </table>
        </div>
    </div>
</div>
<div id="Chart" class="tabcontent">
    <button onclick="goBack(event)">Go Back</button>
    <button onclick="toggle_precision();">Toggle number precision</button>
    <h1>Total run time</h1>
    <div class="ct-chart1"></div>
    <h1>Total number of tuples</h1>
    <div class="ct-chart2"></div>
    <!--<h1>Copy time</h1>-->
    <!--<div class="ct-chart3"></div>-->
    <!--<button onclick="show_graph_vals=!show_graph_vals;draw_graph();">Toggle values</button>-->
</div>
<div id="Code" class="tabcontent">
    <button onclick="goBack(event)">Go Back</button>
    <h3>Source Code</h3>
    <div id="code-view">
        <ol id="code-list"></ol>
    </div>
</div>
</div>
)___";
std::string htmlBodyBottom = R"___(
</body>
</html>

)___";
}
}
}
