<?php


function w20_folder_breadcrumb($tid) {

	$link = '<ul class="w20-folder-breadcrumb-lista"><li class="w20-folder-breadcrumb breadcrumb-root">'.l(t('Início'), url('w20/folder', array('absolute' => TRUE))).'</li>';
	if ($tid != 0 AND $tid != '') {
		$array = array_reverse(taxonomy_get_parents_all($tid), false);
		$count=1;
		foreach($array AS $var) {
			$varTextClean = w20_folder_make_my_text_clean($var -> name);
			$firstclass = $count == 1 ? 'w20-folder-breadcrumb-firstclass' : '';
			$link .= ' <li class="w20-folder-breadcrumb split-item">&raquo;</li> <li class="w20-folder-breadcrumb '.$firstclass.' ">' . l($var -> name, url('w20/folder/' . $var -> tid, array('absolute' => TRUE))).'</li>';
		$count++;	
		}
		$link .= '<li class="w20-folder-breadcrumb-edit"><div class="w20-folder-breadcrumb-img-engrenagem">' . l(theme('image', drupal_get_path('module', 'w20_folder') .'/img/engrenagem.png'), url('w20/folder/' . (int) $var -> tid . '/edit', array('absolute' => TRUE)), array('html' => true)).'</div></li>';
	}
	$link .= '</ul>';
	return $link;
}

function w20_folder_make_my_text_clean($textToChange){
	if (function_exists('transliteration_get')) {
		
		$chagedTxt = transliteration_get($textToChange, $unknown, $source_langcode);//retira os acentos
		
		$chagedTxt = str_replace(' ', '-', $chagedTxt);//insere o caracter no lugar do espaço
 		
 		$chagedTxt = strtolower($chagedTxt);//transforma em caixa baixa
 		
 		return $chagedTxt;
	} 
}
?>
